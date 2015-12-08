#include <iostream>
#include "hash.h"
#include <QTime>
using namespace std;


QString getRandomString(int length);
int random(int min, int max);
void analyzeHash(Hash<int> &h);

int main()
{
    qsrand((uint)QTime::currentTime().msec());

    Hash<int> RSHashObj_1(100, RS);
    analyzeHash(RSHashObj_1);
    Hash<int> RSHashObj_2(10000, RS);
    analyzeHash(RSHashObj_2);
    Hash<int> RSHashObj_3(1000000, RS);
    analyzeHash(RSHashObj_3);

    Hash<int> JSHashObj_1(100, JS);
    analyzeHash(JSHashObj_1);
    Hash<int> JSHashObj_2(10000, JS);
    analyzeHash(JSHashObj_2);
    Hash<int> JSHashObj_3(1000000, JS);
    analyzeHash(JSHashObj_3);

    Hash<int> PJWHashObj_1(100, PJW);
    analyzeHash(PJWHashObj_1);
    Hash<int> PJWHashObj_2(10000, PJW);
    analyzeHash(PJWHashObj_2);
    Hash<int> PJWHashObj_3(1000000, PJW);
    analyzeHash(PJWHashObj_3);

    Hash<int> ELFHashObj_1(100, ELF);
    analyzeHash(ELFHashObj_1);
    Hash<int> ELFHashObj_2(10000, ELF);
    analyzeHash(ELFHashObj_2);
    Hash<int> ELFHashObj_3(1000000, ELF);
    analyzeHash(ELFHashObj_3);

    Hash<int> BKDRHashObj_1(100, BKDR);
    analyzeHash(BKDRHashObj_1);
    Hash<int> BKDRHashObj_2(10000, BKDR);
    analyzeHash(BKDRHashObj_2);
    Hash<int> BKDRHashObj_3(1000000, BKDR);
    analyzeHash(BKDRHashObj_3);

    Hash<int> SBDMHashObj_1(100, SBDM);
    analyzeHash(SBDMHashObj_1);
    Hash<int> SBDMHashObj_2(10000, SBDM);
    analyzeHash(SBDMHashObj_2);
    Hash<int> SBDMHashObj_3(1000000, SBDM);
    analyzeHash(SBDMHashObj_3);

    Hash<int> DJBHashObj_1(100, DJB);
    analyzeHash(DJBHashObj_1);
    Hash<int> DJBHashObj_2(10000, DJB);
    analyzeHash(DJBHashObj_2);
    Hash<int> DJBHashObj_3(1000000, DJB);
    analyzeHash(DJBHashObj_3);

    Hash<int> DEKHashObj_1(100, DEK);
    analyzeHash(DEKHashObj_1);
    Hash<int> DEKHashObj_2(10000, DEK);
    analyzeHash(DEKHashObj_2);
    Hash<int> DEKHashObj_3(1000000, DEK);
    analyzeHash(DEKHashObj_3);

    Hash<int> BPHHashObj_1(100, BPH);
    analyzeHash(BPHHashObj_1);
    Hash<int> BPHHashObj_2(10000, BPH);
    analyzeHash(BPHHashObj_2);
    Hash<int> BPHHashObj_3(1000000, BPH);
    analyzeHash(BPHHashObj_3);

    Hash<int> FNVHashObj_1(100, FNV);
    analyzeHash(FNVHashObj_1);
    Hash<int> FNVHashObj_2(10000, FNV);
    analyzeHash(FNVHashObj_2);
    Hash<int> FNVHashObj_3(1000000, FNV);
    analyzeHash(FNVHashObj_3);

    Hash<int> APHHashObj_1(100, APH);
    analyzeHash(APHHashObj_1);
    Hash<int> APHHashObj_2(10000, APH);
    analyzeHash(APHHashObj_2);
    Hash<int> APHHashObj_3(1000000, APH);
    analyzeHash(APHHashObj_3);

    return 0;
}

int random(int min, int max){
    return qrand() % ((max +1) -min) + min;
}

QString getRandomString(int length){
    static const QString alphanum =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

    QString randString;

    for (int i = 0; i < length; ++i) {
        randString.append(alphanum[ random(0, alphanum.size()-1)]);
    }

    return randString;
}


void analyzeHash(Hash<int> &h){
    bool collisionDetected = false;
    int maxCollisions = 0;

    cout << "Hash Type: "<< h.getHashType().toLocal8Bit().constData()<<endl;
    for (int i = 1; i <= h.size(); ++i) {

        //get depth value at insert
        int depth = h.Add(getRandomString(random(5,10)), i);

        //indicate collision occured
        if(!collisionDetected && depth > 1){
            collisionDetected = true;
            cout << "First colllision at insert #"<<i<< " out of "<< h.size()
                 <<" : "<<i/static_cast<float>(h.size())<<endl;
        }
        maxCollisions = qMax(maxCollisions, depth);
    }
    //display max collisions
    cout << "Maximum colllision depth: "<<maxCollisions<<"\n\n";

}
