//#include <vector>
#include <map>
#include "World/World.h"
//#include "Map.h"

using namespace std;

class Robot;
class Collector;
class Sapper;

class Server
{
public:
    Server(GameArea *actualGameArea) : actualGameArea(actualGameArea), collectedDiamondsAmount(0){};
    //Server() : actualGameArea(nullptr), collectedDiamondsAmount(0) {}
    ~Server() = default;

    bool isCellAvaliable(const Coordinates &coordinates) const;

    size_t GetCollectedDiamondsAmount() { return collectedDiamondsAmount; };

    auto GetDiamondsAvaliable() { return &diamondsAvaliable; };
    auto GetBombsAvaliable() { return &bombsAvaliable; };

    void SetActualMap(GameArea *actualMap) { this->actualGameArea = actualMap; }
    GameArea *GetActualMap() { return this->actualGameArea; }

    void notifyRobotCreated(Robot *robot, const Coordinates &coordinates);
    void notifyRobotDeleted(Robot *robot, const Coordinates &coordinates);

    void notifyDiamondCollected(Robot *robot, const Coordinates &coordinates);
    void notifyBombDefused(Robot *robot, const Coordinates &coordinates);
    void notifyRobotMoved(const Robot *robot, const Coordinates &prevCoordinates, const Coordinates &newCoordinates);
    void notifyCellScanned(Robot *robot, const pair<Coordinates, CellType> scannedCell);

    void applyOthersRobotsChanges();

private:
    GameArea *actualGameArea;
    vector<pair<Coordinates, Robot *>> robotsCoordinates;

    size_t collectedDiamondsAmount;

    vector<Coordinates> diamondsAvaliable;
    vector<Coordinates> bombsAvaliable;

    map<Robot *, vector<pair<Coordinates, CellType>>> robotsChanges;
};