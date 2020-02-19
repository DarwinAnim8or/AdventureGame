#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>

int main()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound.wav"))
		return -1;

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

		return 0;
}