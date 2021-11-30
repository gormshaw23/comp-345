#pragma once
#include <iostream>
#include <list>
#include <vector>
#include<string>

#include "Player/Player.h"
#include "../GameLog/LoggingObserver.h"
#include "../CommandProcessor/CommandProcessor.h"

class Player;
class Map;

//game state
enum GameState
{
    GAME_STATE_UNKNOWN = 0,
    GAME_STATE_START = 1,
    GAME_STATE_MAP_LOAD = 2,
    GAME_STATE_MAP_VALIDATED = 3,
    GAME_STATE_PLAYERS_ADDED = 4,
    GAME_STATE_PLAY = 5,
    GAME_STATE_MAX = 0XFFFF,//set a max value to prevent overflow

};
//user input
enum game_user_input {
    LOADMAP,
    VALIDATEMAP,
    ADDPLAYER,
    GAMESTART,
};

class GameEngine : virtual public Subject, virtual  public ILoggable /*,  public CommandProcessor*/ {
public:
    GameEngine(); //constructor

    GameEngine(Observer*); //constructor
    ~GameEngine(); //destructor
    CommandProcessor* commandProces;
    using Subject::Notify;
    GameEngine(const GameEngine& gm); //copy constructor
    GameState getCurrentState(); //getter

    void game_run();
    virtual std::string stringToLog() override;
    GameEngine& operator=(const GameEngine& obj);//Assignment operator

    Player* getNeutralPlayer() const;

    void mainGameLoop(std::vector<Player*> players, Map* map, int maxNumberOfTurns); //Game loop function

    void startupPhase();


    static GameEngine& getInstance();
private:
    GameState* eState;
    void setCurrentState(GameState eState);
    const void reinforcementPhase(Player* p, Map* m);
    const void issueOrdersPhase(Player* p, Map* map);
    const void executeOrdersPhase(Player* p);
    void gamestart();
    std::string extractName(std::string);//extract name from loadmap and addplayer command
    void addPlayer(std::string);//add player

    Player* neutralPlayer = nullptr;

    bool isATournament; //Determines if a game is part of a tournament
};




