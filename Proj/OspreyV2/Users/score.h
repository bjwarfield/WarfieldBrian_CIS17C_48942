#ifndef SCORE_H
#define SCORE_H


class Score
{
private:
    Score();
    static bool submitted;
    static int score;
    static int kills;
    static int deaths;

    static void reset(){
        submitted = false;
        score = 0;
        kills = 0;
        deaths = 0;
    }

    static void addScore(int value){score += value;}
    static int getScore() {return score;}
    static void addKill(){kills++;}
    static int getKills(){return kills;}
    static void addDeath(){deaths++;}
    static int getDeaths(){return deaths;}
    static bool submit(){
        if(submitted){
            return false;
        }else{
            //TODO DBConnect::submitScore(User::getUserID(), score, kills, deaths);
            submitted = true;
            return true;
        }
    }



public:
};

#endif // SCORE_H
