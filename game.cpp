#include "game.h"
#include "map.cpp"
#include "entities/entity.cpp"
#include "entities/enemy.cpp"
#include "entities/player.cpp"

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

template<class T>
T* Game::Spawn() {
  T* NewInstance = new T();
  Entities.push_back(static_cast<Entity*>(NewInstance));

  return NewInstance;
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
  if (ch == KEY_DOWN) {
    CurrentPlayer->MoveDown();
  }
  else if (ch == KEY_UP) {
    CurrentPlayer->MoveUp();
  }
  else if (ch == KEY_LEFT) {
    CurrentPlayer->MoveLeft();
  }
  else if (ch == KEY_RIGHT) {
    CurrentPlayer->MoveRight();
  }
}

void Game::Run() {
  Draw();

  int ch = getch();

  while(ch != 'q' && ch != 'Q') {
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
      CurrentMap->UpdateEntities(Entities);
      i++;
    } else {
      Entities.erase(i);
    }
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
  printw("Cool Game");
};
