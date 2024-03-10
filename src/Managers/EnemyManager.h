#pragma once 

#include "playerShip.h"

// Section for enemy types
#include "EnemyCruiser.h"
#include "EnemyVanguard.h"

// Section for Bosses
#include "ORT.h"
#include "UFO.h"

class EnemyManager {
    //==================== Utility Functions and Variables ====================
    public:
        static ofVec2f getRandomEdgePoint();
        static int pointsPerUpdateCycle;
        static int getPointsScored() { return pointsPerUpdateCycle; }

    private:
        // static unique_ptr<EnemyShip> currentBoss;
        static int enemySpawnTimer;
        static int killSpreeTimer;

    //==================== Enemy and Bullet Management ====================
    public:
        // Enemy Management
        static bool toggleHitBoxes;
        static vector<unique_ptr<EnemyShip>> enemyList;
        static vector<unique_ptr<Boss>> bossList; // A separate list to keep track of bosses
        static vector<unique_ptr<EnemyShip>> enemiesForDeletion; // Enemies queued for deletion

        // Main Logic
        static void updateEnemies(Player* player); // Main method of the class, handling overall enemy management
        static void spawnEnemy(Player* player); // Handles the logic for spawning new enemies based on game state
        static void removeEnemies(); // Handles the removal of dead enemies from the game
        



    //Boss Management
    private:
        static bool bossIsSpawning;
        static string whichBoss;
        static int bossWarningTimer;
        static bool bossIsActive;
        static bool ufoSeen;
        static bool ortSeen;


    public:
        // Boss Management
        static bool isBossSpawning();
        static void initiateBossSpawn(string bossType); // Initiates the spawning of a boss (used for the warning)
        static void decrementBossWarningTimer();
        static int getBossWarningTimer();
        static void resetBossWarningTimer(int value);

        static string getSpawningBossType(); 
        static void updateBossWarningTimer(float deltaTime); 

        static void spawnBoss(const string& bossType); // Handles the logic for spawning bosses
        static void bossHasDied(); // Handles logic when a boss dies

        // Collision and Bullet Management
        static void manageCollisions(Player* player); // Handles collision detection and response
        static void updateEnemyBullets(EnemyShip* enemy); // Updates positions of enemy bullets
        static void deleteMarkedBullets(); // Cleans up bullets marked for deletion

        // Utility Methods
        static void cleanUp(); // Cleans up resources, ensuring proper memory management

        // Drawing
        static void drawEnemies(); // Draws enemies on the screen
        static void drawEnemyBullets(EnemyShip& enemy); // Draws bullets for each enemy

    //==================== Helper Functions ====================
        static void decrementKillSpreeTimer();
        static int getKillSpreeTimer();
        static void resetKillSpreeTimer(int value);
        static int whichSpawnInterval(int playerScore); // Determines the interval for spawning enemies based on player score
};