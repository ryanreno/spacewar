#include "GameManager.hpp"

#include "EntityFactory.hpp"

#include <iostream>

GameManager::GameManager(
    const TextureManager &textureManager,
    const SoundManager &soundManager,
    const TextManager &textManager,
    const FontManager &fontManager,
    entityx::EntityManager &entityManager,
    entityx::EventManager &eventManager):
        mTextureManager(textureManager),
        mSoundManager(soundManager),
        mTextManager(textManager),
        mFontManager(fontManager),
        mEntityManager(entityManager),
        mEventManager(eventManager),
        mGameState(GameState::Unknown)
{
    subscribeEvents();
}

void GameManager::subscribeEvents()
{
    mEventManager.subscribe<LaunchGameEvent>(*this);
    mEventManager.subscribe<StartGameEvent>(*this);
    // mEventManager.subscribe<PauseGameEvent>(*this);
    // mEventManager.subscribe<ResumeGameEvent>(*this);

    /* Note the Game class is subscribed to the QuitGameEvent directly */
}

void GameManager::receive(
    const LaunchGameEvent &launch)
{
    (void)launch;

    StartMenuCreator creator(mTextManager, mFontManager);
    creator.create(mEntityManager.create());
}

void GameManager::receive(
    const StartGameEvent &event)
{
    /* Blows away all the entities, which clears the menu. */
    mEntityManager.reset();
}
