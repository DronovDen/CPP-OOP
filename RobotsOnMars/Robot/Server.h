//#include <vector>

#include "../World/World.h"

//#include "Map.h"

using namespace std;

class Robot;
class Collector;
class Sapper;

class Server
{
public:
    Server() : actualGameArea(nullptr), collectedDiamonds(0) {}
    Server(GameArea *actualGameArea) : actualGameArea(actualGameArea), collectedDiamonds(0){};
    ~Server() = default;

    bool IsCellAvaliable(const Coordinates &coordinates) const;

    size_t GetCollectedDiamondsNum() { return collectedDiamonds; };

    auto GetDiamondsAvaliable() { return &diamondsAvaliable; };
    auto GetBombsAvaliable() { return &bombsAvaliable; };

    void SetActualGameArea(GameArea *actualMap) { this->actualGameArea = actualMap; }
    GameArea *GetActualGameArea() { return this->actualGameArea; }

    void NotifyRobotCreated(Robot *robot, const Coordinates &coordinates);
    void NotifyRobotDeleted(Robot *robot, const Coordinates &coordinates);

    void NotifyDiamondCollected(Robot *robot, const Coordinates &coordinates);
    void NotifyBombDefused(Robot *robot, const Coordinates &coordinates);
    void NotifyRobotMoved(const Robot *robot, const Coordinates &prevCoordinates, const Coordinates &newCoordinates);
    void NotifyCellScanned(Robot *robot, const pair<Coordinates, CellType> scannedCell);

    void applyOthersRobotsChanges();

private:
    GameArea *actualGameArea;
    vector<pair<Coordinates, Robot *>> robotsCoordinates;
    unordered_map<Robot *, vector<pair<Coordinates, CellType>>> robotsCache; //vector of robots changes

    size_t collectedDiamonds;
    vector<Coordinates> diamondsAvaliable;
    vector<Coordinates> bombsAvaliable;
};