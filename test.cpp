#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
  srand((unsigned)(time(NULL)));

  int XSize = std::stoi(argv[1]);
  int YSize = std::stoi(argv[2]);
  int RoomsAmount = std::stoi(argv[3]);

  float Multiplier = std::sqrt((XSize * YSize) / RoomsAmount);
  int XRoomSize = XSize / std::round(XSize / Multiplier);
  int YRoomSize = YSize / std::ceil(YSize / Multiplier);

  // rooms stuff calculated, find out start and end rooms

  bool ChooseVertical = (int)rand() % 2 == 0;
  int Offset = (rand() % (ChooseVertical ? YSize / YRoomSize : XSize / XRoomSize));

  // choose finish room

  // TODO: Modify to not make absent room finish
  int FinishOffset = (rand() % (ChooseVertical ? YSize / YRoomSize : XSize / XRoomSize));

  for(int y = 0; y < YSize + 1; y++) {
    for(int x = 0; x < XSize + 1; x++) {
      if ((y - 1) / YRoomSize * XSize / XRoomSize + (x - 1) / XRoomSize + 1 > RoomsAmount) {
        break;
      }

      if (x / (float)XRoomSize > XSize / XRoomSize) {
        break;
      }

      bool bPass = (int)rand() % 10 == 0;

      if ((x == 0) || (x >= XRoomSize && (x % XRoomSize == 0)) || ((y == 0) || (y >= YRoomSize && (y % YRoomSize == 0)))) {
        if (bPass && x > 0 && x < XSize && y > 0 && y < YSize) {
          std::cout << " ";
        } else {
          std::cout << "X";
        }
      } else {
        if (ChooseVertical &&
            (y / YRoomSize >= Offset) &&
            (y / YRoomSize <= Offset) &&
            (x / XRoomSize < 1.f)) {
          std::cout << "S";
        } else if (!ChooseVertical &&
                   (x / XRoomSize >= Offset) &&
                   (x / XRoomSize <= Offset) &&
                   (y / YRoomSize < 1.f)) {
          std::cout << "S";
        } else if (ChooseVertical &&
                   (y / YRoomSize >= FinishOffset) &&
                   (y / YRoomSize <= FinishOffset) &&
                   (x / XRoomSize == XSize / XRoomSize - 1)) {
          std::cout << "F";
        } else if (!ChooseVertical &&
                   (x / XRoomSize >= FinishOffset) &&
                   (x / XRoomSize <= FinishOffset) &&
                   (y / YRoomSize == YSize / YRoomSize - 1)) {
          std::cout << "F";
        } else {
          std::cout << " ";
        }
      }
    }
    std::cout << "\n";
  }
}
