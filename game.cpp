#include "game.h"
#include "map.cpp"
#include "entities/entity.cpp"
#include "entities/enemy.cpp"
#include "entities/player.cpp"
#include "entities/actions/action.h"

Game::Game() {
  CurrentMap = new Map();
  InitializePlayer();

  // TODO: Remove test section
  Enemy* T = Spawn<Enemy>();
  T->SetTarget(CurrentPlayer);

  CurrentMap->UpdateEntities(Entities);
}

Game* Game::GetInstance() {
  if (Instance == 0) {
    Instance = new Game();
  }

  return Instance;
}

void Game::AddMessage(string NewMessage) {
  Messages.push_back(NewMessage);
}

template<class T>
T* Game::Spawn() {
  shared_ptr<T> NewInstance(new T());
  Entity* EntityInstance = static_cast<Entity*>(NewInstance.get());
  Entities.push_back(EntityInstance);
  EntityInstance->SetThisPtr(NewInstance);

  return NewInstance.get();
}

void Game::Over() {
  bIsRunning = false;
}

Map* Game::GetMap() const {
  return CurrentMap;
}

Player* Game::GetPlayer() const {
  return CurrentPlayer;
}

void Game::InitializePlayer() {
  CurrentPlayer = Spawn<Player>();
}

void Game::ConsumePlayerInput(int ch) {
  CurrentPlayer->ProcessInput(ch);
}

void Game::Run() {
  Draw();

  int ch = getch();

  while(bIsRunning && ch != 'q' && ch != 'Q') {
    if (ch > 0) {
      // Process input
      ConsumePlayerInput(ch);

      Draw();
    }

    // Read new character
    ch = getch();
  }
};

void Game::Draw() {
  wmove(stdscr, 0, 0);

  for (vector<Entity*>::iterator i = Entities.begin(); i != Entities.end(); ) {
    Entity* entity = *i;

    if (!entity->GetIsMarkedForDestroy()) {
      entity->PerformTurn();
      i++;
    } else {
      Entities.erase(i);
    }

    CurrentMap->UpdateEntities(Entities);
  }

  // Draw Map
  for (int y = 0; y < CurrentMap->HorizontalSize(); y++) {
    for (int x = 0; x < CurrentMap->VerticalSize(); x++) {
      int ColorPair = CurrentMap->GetColorAtLocation(x, y);
      attron(COLOR_PAIR(ColorPair));
      printw(CurrentMap->GetCharAtLocation(x, y).c_str());
      attroff(COLOR_PAIR(ColorPair));
    }
    printw("\n");
  }

  // Draw UI
  wmove(stdscr, CurrentMap->HorizontalSize(), 0);

  printw("Health: %.1f / %.1f\n",
         CurrentPlayer->GetAttributes()->GetHealth(),
         CurrentPlayer->GetAttributes()->GetMaxHealth());

  const vector<Action*> Actions = CurrentPlayer->GetActions();

  for(int i = 0; i < Actions.size(); i++) {
    printw("| Action %d - %s |", i, Actions[i]->GetName().c_str());
  }

  // Print messages
  for(int i = 0; i < Messages.size(); i++) {
    mvprintw(i, CurrentMap->VerticalSize(), Messages[i].c_str());
  }
  Messages.clear();
};
