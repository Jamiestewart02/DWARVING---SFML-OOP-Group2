#include "Player.h"

/*Player class was made by Darren -- This handles game physics, core gameplay mechanics and how the player character
interacts with all other aspects of the game. Any use of the player class within the game was implemented by me.*/

/*===============================================
			SETTERS
===============================================*/

void Player::setPosition(float x, float y) {
	this->playerPosition.x = x;
	this->playerPosition.y = y;
}

void Player::setSize(float w, float h) {
	this->playerWidth = w;
	this->playerHeight = h;
}

void Player::setColour(sf::Color colour) {
	this->colour = colour;
}

void Player::setShapeColour(sf::Color colour) {
	rect.setFillColor(colour);
}

//defines the player character and the collision boxes
void Player::setShape() {
	rect.setSize({ playerWidth, playerHeight });
	rect.setPosition({ playerPosition.x, playerPosition.y });
	topBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 1.f, playerPosition.y - rect.getGlobalBounds().height / 4 });
	leftBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 - leftBound.getGlobalBounds().width, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	rightBound.setPosition({ playerPosition.x + rect.getGlobalBounds().width / 4, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	bottomBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 5.f, playerPosition.y + rect.getGlobalBounds().height / 2 + 1.f });
}

void Player::setGroundHeight(float height) {
	groundHeight = height;
}

void Player::setGrappleVelocity(float velx, float vely) {
	playerVelocity.x = velx;
	playerVelocity.y = vely;
}

void Player::setIndirVelX(float vel) {
	indirVelX = vel;
}

void Player::setOnLedge(bool onLedge) {
	this->onLedge = onLedge;
}

void Player::setAnchor(bool anchor) {
	anchored = anchor;
}

void Player::setVelY(float vely) {
	playerVelocity.y = vely;
}

void Player::setHealthToMax() {
	playerHealth.x = 100.f;
}

void Player::setHealthBarPosition(float x, float y) {
	this->healthBarX = x;
	this->healthBarY = y;
}

void Player::setTexture() {
	texture.loadFromFile(animation.fileName);
}

/*===============================================
			GETTERS
===============================================*/

float Player::getPositionX() {
	return playerPosition.x;
}

float Player::getPositionY() {
	return playerPosition.y;
}

sf::Vector2f Player::getPosition() {
	return this->playerPosition;
}

float Player::getPlayerWidth() {
	return playerWidth;
}

float Player::getPlayerHeight() {
	return playerHeight;
}

float Player::getGroundHeight() {
	return this->groundHeight;
}

sf::FloatRect Player::getBounds() {
	return rect.getGlobalBounds();
}

float Player::getVelY() {
	return playerVelocity.y;
}

sf::RectangleShape Player::getShape() {
	return rect;
}

bool Player::getAnchor() {
	return this->anchored;
}

float Player::getVelX() {
	return this->playerVelocity.x;
}

bool Player::getOnLedge() {
	return this->onLedge;
}

sf::Vector2f Player::getDistanceBetween() {
	return this->distanceBetween;
}

float Player::getHealthBarPositionX() {
	return healthBarX;
}

float Player::getHealthBarPositionY() {
	return healthBarY;
}

float Player::getDecreaseHealth() {
	return decreaseHealth;
}

sf::Vector2f Player::getPlayerHealth() {
	return playerHealth;
}

/*Gets the trajectory angle of the player's position and another point.
Passes in the x & y distances of the two points*/
float Player::getAngle(float sideX, float sideY) {

	float tanOfSides = sideY / sideX;

	float angle = atan(tanOfSides) * (180 / 3.14159);

	return angle;
}

/*===============================================
			SHOOTING MECHANICS
===============================================*/

/*Allows the character to shoot if the user clicks on the screen(in front of where the character is facing), 
if the bow is equipped, and if an arrow doesn't aready exist on the screen.
WARNING:: A wireless mouse seems to cause the aiming to malfunction. Maybe mouse calibration??*/
void Player::setShot(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed && bullet.getScale().x == 0.f) {
		if (!animation.flipped) {
			if (event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(window).x < playerPosition.x && isBow) {
				shot = true;
			}
		}

		if (animation.flipped) {
			if (event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(window).x > playerPosition.x && isBow) {
				shot = true;
			}
		}
	}
}

/*Pythagoras to find distance of two points to get the inverse of distance*/
void Player::setBulletDistanceBetween(sf::Vector2i targetDistance) {
	bulletDistanceBetween.x = targetDistance.x - (bullet.getPosition().x);
	bulletDistanceBetween.y = targetDistance.y - (bullet.getPosition().y);

	float distance = sqrt((bulletDistanceBetween.x * bulletDistanceBetween.x) + (bulletDistanceBetween.y * bulletDistanceBetween.y));
	bulletInverseDistance = 1.f / distance;
}

/*Apply the inverse distance to adjust the bullet velocity*/
void Player::setBulletVelocity() {
	float normalisedDistanceX = bulletDistanceBetween.x * bulletInverseDistance;
	float normalisedDistanceY = bulletDistanceBetween.y * bulletInverseDistance;

	bulletVelocity.x = normalisedDistanceX * 15.f;
	bulletVelocity.y = normalisedDistanceY * 15.f;
}

/*Character shoots arrow. Applies Pythagoras to set trajectory to where the mouse is clicked.
Applies trigonometry (the setAngle function) to rotate sprite to match trajectory*/
void Player::shoot(std::vector<Platform> ledges, sf::RenderWindow& window) {

	if (shot && isBow) {

		if (animation.flipped) {
			bullet.setPosition((playerPosition.x + rect.getGlobalBounds().width / 4), playerPosition.y);
			bullet.setScale(1.f, 1.f);
		}
		else {
			bullet.setPosition((playerPosition.x - rect.getGlobalBounds().width / 4), playerPosition.y);
			bullet.setScale(-1.f, 1.f);
		}

		setBulletDistanceBetween(sf::Mouse::getPosition(window));
		setBulletVelocity();
		bullet.setRotation(getAngle(bulletDistanceBetween.x, bulletDistanceBetween.y) - 180.f);

		shot = false;
	}

	bullet.move({ bulletVelocity.x, bulletVelocity.y });

	checkBulletCondition(ledges);
}

/*Removes arrow visual if it hits a platform or if it travels off screen*/
void Player::checkBulletCondition(std::vector<Platform> ledges) {
	for (int i = 0; i < ledges.size(); i++) {

		if (bullet.getGlobalBounds().intersects(ledges[i].getBounds())) {

			bullet.setPosition(playerPosition);
			bullet.setScale(0.f, 0.f);
			break;
		}
	}

	if (bullet.getPosition().x > SCREENWIDTH ||
		bullet.getPosition().x < 0.f ||
		bullet.getPosition().y < 0.f) {

		bullet.setPosition(playerPosition);
		bullet.setScale(0.f, 0.f);
	}
}

/*===============================================
			GRAPPLE MECHANICS
===============================================*/

/*Allows the character to grapple if following conditions are met: user clicks on a grapple point; character is below that grapple point;
 if the character isn't already airborne from grappling. If all conditions are met, a pointer of that grapple point is used for the character to grapple to*/
void Player::initiateGrapple(std::vector<sf::Sprite> grapplePoints, std::vector<Platform> platforms, sf::RenderWindow& window) {

	for (int i = 0; i < grapplePoints.size(); i++) {
		sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
		sf::Vector2f tracker = window.mapPixelToCoords(clickPosition);

		if (grapplePoints[i].getGlobalBounds().contains(tracker)) {
			grapplePoint = &grapplePoints[i];
			(*grapplePoint).setOrigin((*grapplePoint).getGlobalBounds().width / 2, (*grapplePoint).getGlobalBounds().height / 2);
			break;
		}
	}

	if (grapplePoint != NULL) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !cangrapple && getPositionY() > (*grapplePoint).getPosition().y) {

			cangrapple = true;
			grappletopoint = true;

			if (!checkGrapplePath(platforms)) {
				cangrapple = false;
				grappletopoint = false;
			}

			if (getPositionX() > (*grapplePoint).getPosition().x) {
				direction = -1.f;
				animation.flipped = false;
			}
			else {
				direction = 1.f;
				animation.flipped = true;
			}
		}
	}
}

/*Uses trigonometry to get bounds and check for a clear path from the character to the grapple point*/
bool Player::checkGrapplePath(std::vector<Platform> ledges) {
	bool pathClear;
	sf::RectangleShape path;

	setDistanceBetween((*grapplePoint).getPosition());
	float tandistance = distanceBetween.y / distanceBetween.x;

	path.setSize({ distance, 2.f });
	path.setPosition(rect.getPosition());

	if (!isLeftOf(playerPosition.x, (*grapplePoint).getPosition().x)) {
		path.setScale(-1.f, 1.f);
	}
	else {
		path.setScale(1.f, 1.f);
	}

	path.setRotation(getAngle(distanceBetween.x, distanceBetween.y));
	sf::FloatRect bounds = path.getGlobalBounds();

	for (int i = 0; i < ledges.size(); i++) {
		if (bounds.intersects(ledges[i].getBounds())) {
			pathClear = false;
			break;
		}
		else {
			pathClear = true;
		}
	}

	return pathClear;
}

/*Sets inverse distance. functions the same way as bullet*/
void Player::setDistanceBetween(sf::Vector2f targetDistance) {
	distanceBetween.x = targetDistance.x - playerPosition.x;
	distanceBetween.y = targetDistance.y - playerPosition.y;
	distance = sqrt((distanceBetween.x * distanceBetween.x) + (distanceBetween.y * distanceBetween.y));
	inverseDistance = 1.f / distance;
}

float Player::getInversedDistance() {
	distance = sqrt((distanceBetween.x * distanceBetween.x) + (distanceBetween.y * distanceBetween.y));
	inverseDistance = 1.f / distance;
	return inverseDistance;
}

/*If all conditions are met, the character grapples. Upon reaching the point, the character recieves indirect dropoff x & y velocity*/
void Player::grapple() {

	if (grapplePoint != nullptr) {

		setDistanceBetween((*grapplePoint).getPosition());

		float normalisedDistanceX = distanceBetween.x * inverseDistance;
		float normalisedDistanceY = distanceBetween.y * inverseDistance;
		float dropoff;

		if (rect.getGlobalBounds().intersects((*grapplePoint).getGlobalBounds()) && grappletopoint == true) {
			grappletopoint = false;
			dropoff = normalisedDistanceX;
			setVelY(10.f * normalisedDistanceY);
		}

		if (dropoff < 0) {
			dropoff = dropoff * -1;
		}

		if (grappletopoint) {
			setIndirVelX(normalisedDistanceX * 10.f);
			setVelY(normalisedDistanceY * 10.f);
		}

		if (grappletopoint == false && cangrapple == true) {
			setIndirVelX(10.f * direction * dropoff);
		}

		if (getPositionY() >= getGroundHeight() - 1.f) {
			cangrapple = false;
			grapplePoint = nullptr;
			setIndirVelX(0.f);
		}

		setPosition((playerPosition.x + playerVelocity.x), (playerPosition.y + playerVelocity.y));
	}
}

/*Sets a line from the player to the grapple point*/
void Player::setRope() {
	if (grapplePoint != nullptr) {
		rope[0].position = sf::Vector2f(playerPosition);
		rope[0].color = sf::Color::Red;
		rope[1].position = sf::Vector2f((*grapplePoint).getPosition().x + ((*grapplePoint).getGlobalBounds().width / 4), (*grapplePoint).getPosition().y + ((*grapplePoint).getGlobalBounds().height / 4));
		rope[1].color = sf::Color::Red;
		rope[2].position = sf::Vector2f((*grapplePoint).getPosition().x + ((*grapplePoint).getGlobalBounds().width / 4), (*grapplePoint).getPosition().y + ((*grapplePoint).getGlobalBounds().height / 4 + 2.f));
		rope[2].color = sf::Color::Red;
		rope[3].position = sf::Vector2f(playerPosition.x, playerPosition.y + 2.f);
		rope[3].color = sf::Color::Red;
		rope[4].position = sf::Vector2f(playerPosition.x, playerPosition.y);
		rope[4].color = sf::Color::Red;
	}
}

void Player::drawRope(sf::RenderWindow& window) {
	window.draw(rope, 5, sf::LineStrip);
}

/*===============================================
			ENVIRONMENT MECHANICS
===============================================*/

//Character movement. Collision boxes move with the character
void Player::movePlayer() {
	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
	rect.setPosition(playerPosition);
	topBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 1.f, playerPosition.y - rect.getGlobalBounds().height / 4 });
	leftBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 - leftBound.getGlobalBounds().width, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	rightBound.setPosition({ playerPosition.x + rect.getGlobalBounds().width / 4, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	bottomBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 5.f, playerPosition.y + rect.getGlobalBounds().height / 2 + 1.f });
	hurtBox.setPosition(playerPosition.x + (rect.getGlobalBounds().width / 4), playerPosition.y + (rect.getGlobalBounds().height / 4));
}

//Moves left and right upon key press
void Player::setVelX() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !cangrapple) {
		playerVelocity.x = -5.f + indirVelX;
		animation.setStartEndPoints(400, 900);
		animation.flipped = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !cangrapple) {
		playerVelocity.x = 5.f + indirVelX;
		animation.setStartEndPoints(400, 900);
		animation.flipped = true;
	}
	else {
		animation.setStartEndPoints(0, 300);
		playerVelocity.x = indirVelX;
	}
}

//Offsets the y velocity by -16. Gravity is added on to this each frame to pull the character back down.
void Player::jump() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerVelocity.y == 0 && lift == true) {
		playerVelocity.y = -16.f;
		lift = false;
		onLedge = false;
		indirVelX = 0.f;
	}

	if (playerPosition.y > (this->groundHeight)) {
		playerPosition.y = this->groundHeight;
		playerVelocity.y = 0;
		lift = true;
		animation.switchTime = 1.0;
	}

	if (playerPosition.y < (this->groundHeight)) {
		if (playerVelocity.y < 13.f) {
			playerVelocity.y += gravity;
			animation.switchTime = 0.3;
		}
	}
}

/*Collision boxes surrounding the character negates corresponding velocity when colliding with a platform*/
void Player::checkBounds(std::vector<Platform> platforms) {

	for (int i = 0; i < platforms.size(); i++) {

		if (bottomBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			setOnLedge(true);
			anchor(platforms[i]);
			break;
		}
		else {
			setOnLedge(false);
			setGroundHeight(SCREENHEIGHT);
		}
	}

	for (int i = 0; i < platforms.size(); i++) {

		if (rightBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			if (getVelX() > 0.f) {
				playerVelocity.x = 0.f;
				break;
			}
		}
	}

	for (int i = 0; i < platforms.size(); i++) {

		if (leftBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			if (getVelX() < 0.f) {
				playerVelocity.x = 0.f;
				break;
			}
		}
	}

	for (int i = 0; i < platforms.size(); i++) {

		if (topBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			if (getVelY() < 0.f) {
				playerVelocity.y = 0.f;
				break;
			}
		}
	}
}

/*Detects if the player comes into contact with the door. Level completes when collision occurs*/
void Player::checkDoor(Level& level) {
	if (level.leverPulled && rect.getGlobalBounds().intersects(level.door.getGlobalBounds())) {

		if (level.levelTwoComplete && level.levelOneComplete) {
			level.levelThreeComplete = true;;
		}
		else if (level.levelOneComplete) {
			level.levelTwoComplete = true;
		}
		else {
			level.levelOneComplete = true;
		}
		level.levelSwitch = true;
	}
}

//Kills character when collision with a pit occurs
void Player::checkForSpikes(std::vector<Platform> deathZones) {

	for (int i = 0; i < deathZones.size(); i++) {
		if (rect.getGlobalBounds().intersects(deathZones[i].getBounds())) {
			animation.coordinates.left = 1600;
		}
	}
}

//Suspends player on top of platform. Negating gravity and indirect x velocity
void Player::anchor(Platform platform) {
	setIndirVelX(0.f);

	if (getOnLedge()) {
		setGroundHeight(platform.getPositionY() - rect.getGlobalBounds().height / 2 + 1.f);
	}
	else {
		setIndirVelX(0.f);
	}
}

/*===============================================
			COMBAT MECHANICS
===============================================*/

/*Character runs through the attack animation if the right button is clicked.
If isBow is true then the character shoots an arrow*/
void Player::attack(std::vector<Platform> ledges, sf::RenderWindow& window) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !cangrapple) {
		if (isBow) {
			if (bullet.getScale().x == 0.f) {
				animation.attack = true;
				setSFX("assets/sfx_bowAttack.wav"); //anthony
			}
		}
		else {
			animation.attack = true;
			setSFX("assets/sfx_pickaxeAttack.wav"); //anthony
		}
	}
	if (animation.attack == true) {
		animation.setStartEndPoints(1000, 1300);
		animation.switchTime = 0.7;

		if (animation.coordinates.left >= animation.endPoint) {
			animation.attack = false;
			animation.setStartEndPoints(0, 300);
			animation.switchTime = 1;
		}
	}
	if (isBow) {
		shoot(ledges, window);
	}
	else {
		bullet.setPosition(playerPosition);
		bullet.setScale(0.f, 0.f);
	}
}

//Damages the character, giving a brief period of damage immunity
void Player::setPlayerHealth() {
	damageTime++;

	if (damageTime >= immuneTime) {
		playerHealth.x -= decreaseHealth;
		damageTime -= immuneTime;
	}

	if (playerHealth.x < 0) {
		playerHealth.x = 0;
	}
	if (playerHealth.x <= 0) {
		animation.setStartEndPoints(1400, 1600);
		animation.switchTime = 0.7;
		healthBar.setFillColor(sf::Color::Transparent);
	}
}

//resizes the healthbar according to the player's health
void Player::setHealthBarShape() {
	healthBar = sf::RectangleShape(playerHealth);
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setPosition(healthBarX, healthBarY);
	healthBar.setScale(2.f, 1.f);

}

bool Player::isLeftOf(float currentPositionX, float targetPositionX) {
	if (currentPositionX < targetPositionX) {
		return true;
	} else {
		return false;
	}
}

//One hit death for character when Dwarf Must Die Mode is activated
void Player::dwarfMustDieMode() {
	immuneTime = 0;
	playerHealth.x = 10.f;
}

//method for defining sound effects. -- Anthony
void Player::setSFX(std::string sfxFileName) {
	sfxBuffer.loadFromFile(sfxFileName);
	sound.setBuffer(sfxBuffer);
	sound.setVolume(10.f);
	sound.play();
}

//Updates the character's condition every frame
void Player::update(std::vector<Platform> platforms, std::vector<Platform> deathZones, sf::RenderWindow& window) {
	jump();
	movePlayer();
	checkForSpikes(deathZones);
	attack(platforms, window);
	animation.Animate(rect, animation.switchTime);
	setHealthBarShape();
	window.draw(healthBar);
	window.draw(rect);
}