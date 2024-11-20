#pragma once
#include "troops/soldier.h"
#include "troops/catapult.h"
#include "troops/specialbuilds.h"
#include "building.h"
#include "help/array2d.h"
enum BaseType{Nothing,TroopType,BuildingType};
enum PlayerType{Computer,Real};
TInfo::TroopTypes GetTroopType(BuildingTypes Build);
BuildingTypes GetBuildType(TInfo::TroopTypes Troop);
Troop * MakeNewTroop(TInfo::TroopTypes TType, Point AtSpot);
BuildingTypes AttBuildReqs(Attach::Attachment Attach);
Attach::AttachList BuildAttachMake(BuildingTypes Build);
void ChangeOverallTurn();
void MakeDialogue(string S,string H);//this should be obsoleted!
void AttackLocation(Point Loc,Troop * AttackingTroop);
bool AttemptAttack(Point Loc,Troop * AttackingTroop);
int GetDominationOfTroop(int Range, int Distance);
extern Array2d<int> PlayerOcc;
extern Array2d<Domination> PlayerDom;
class Player
{
public:
    Player(void);
    virtual ~Player(void);
    Player(Player * CopyFrom);//deep copy constructor
    virtual void DeepCopy(Player * CopyFrom);
    int PlayerNum;
    PlayerType Type;
    int Money;
    int MiniTurn;
    int TeamNum;
    bool CurrentTurn;
    vector<Troop *> Troops;
    vector<Building *> Buildings;
    Array2d<BaseType> TPlayerMap;
    Array2d<int> NPlayerMap;
    virtual void Save(ofstream & File);
    virtual void Load(ifstream & File);
    virtual void ClearData();
    virtual void operator = (Player & CopyFrom){ DeepCopy(&CopyFrom); }
    void ResetStats();
    int GetBuyAmmounts(BuildingTypes Build,Point GetSpot);
    void SubtractBuyAmmountByOne(BuildingTypes Build,Point SubSpot);
    bool BuyAttach(Attach::Attachment Attach,Troop * T);
    bool CanBuyAttach(Attach::Attachment Attach,Troop * T);
    void StartNew();
    virtual void DoAITurn(vector<Player *> & InPlayers){}
    virtual void RightClick(Point ClickP) {}
    virtual void LeftClick(Point ClickP) {}
    virtual void MouseMove(Point MouseLoc) {}
    virtual void SelectThing(SelectTypes Build){}
    virtual void PlaceNewTroop(Point spot,TInfo::TroopTypes ThingType);
    void PlayerAttackLocation(Point Loc,Troop * AttackingTroop);
    bool PlaceNewBuilding(BuildingTypes Build,int x1,int y1,int x2,int y2);
    virtual void RemoveThingCompletely(BaseType ThingType, int Item);
    virtual void ShowOnScreen();
    BaseType GetMyBType(Point P);
    Troop * GetMyTroop(Point P);
    Building * GetMyBuild(Point P);
    bool AttemptAttackOnOthers(int TroopNum,Point Loc);
    bool AttemptAttackOnSelf(Point Loc,Troop * AttackingTroop);
    virtual bool ChangeTurn();//returns true if it changes the overall turn to the next player
    bool MoveTroop(int TroopNum,Point FinalPoint);
    void AssertDommination();
    int GetIncomeFromBuildings();
    bool CheckMovement(Point Start, Point End, int MovePoints);
    int GetPointsForMove(Point Start, Point End,int MaxMovePoints);
    bool CheckAngledRange(Point Start, Point Finish);
    bool CheckAttack(Point From, Point To, int Range);
    bool GetPath(vector<Point> & OutPath, Point Start, Point End, int MaxRange = BoardSizeX + BoardSizeY);//arbitrary maxmimum
    bool GetFastPath(vector<Point> & OutPath, Point Start, Point End, int MaxRange = BoardSizeX + BoardSizeY);
    void PlaceWall(Point P1, Point P2);
    vector<Point> GetValidDistances(Building * B, Point GetCloseTo);
};
inline bool OnSameTeam(Player * P1, Player * P2){
    return P1->TeamNum == P2->TeamNum;
}
