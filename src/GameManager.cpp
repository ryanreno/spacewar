#include "GameManager.hpp"

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
    // mEventManager.subscribe<StartGameEvent>(*this);
    // mEventManager.subscribe<QuitGameEvent>(*this);
    // mEventManager.subscribe<PauseGameEvent>(*this);
    // mEventManager.subscribe<ResumeGameEvent>(*this);
}

void GameManager::receive(
    const LaunchGameEvent &launch)
{
    auto splashText = mTextManager.get(TextId::SplashScreen);

    // std::cout << splashText.get() << std::endl;
    // SplashScreenCreator().create()
}
