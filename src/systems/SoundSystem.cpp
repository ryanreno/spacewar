#include "SoundSystem.hpp"

#include "components/Player.hpp"
#include "components/Position.hpp"

SoundSystem::SoundSystem(
    const SoundManager &soundManager,
    entityx::EventManager &eventManager):
        mSoundManager(soundManager),
        mActiveSounds()
{
    eventManager.subscribe<PlaySoundEvent>(*this);
}

void SoundSystem::update(
    entityx::EntityManager &entities,
    entityx::EventManager &events,
    const double dt)
{
    Player::Handle player;
    Position::Handle position;
    for (entityx::Entity e : entities.entities_with_components(player, position))
    {
        setListenerPosition(position->getPos());
    }

    removeStoppedSounds();
}

void SoundSystem::receive(
    const PlaySoundEvent &soundEvent)
{
    const SoundId soundId = soundEvent.get();
    const sf::Vector2f position = getListenerPosition();

    mActiveSounds.push_back(sf::Sound());
    sf::Sound &sound = mActiveSounds.back();
    sound.setBuffer(mSoundManager.get(soundId));

    sound.setPosition(position.x, -position.y, 00.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);
    sound.play();
}

void SoundSystem::removeStoppedSounds()
{
    mActiveSounds.remove_if([] (const sf::Sound &s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

sf::Vector2f SoundSystem::getListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}

void SoundSystem::setListenerPosition(
    const sf::Vector2f &position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}
