#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;

class board{
    public:
        char map[9];
        char s, x, o;
        
        int isDone(char map[9]){
            int xw = 100, ow = -100;
            
            char n = 0;
            for(int i = 0; i < 3; i++){
                //check for horizontal wins
                if(map[n] == x && map[n+1] == x && map[n+2] == x){ return xw; }
                if(map[n] == o && map[n+1] == o && map[n+2] == o){ return ow; }
                n += 3;
                
                //check for vertical wins
                if(map[i] == x && map[i+3] == x && map[i+6] == x){ return xw; }
                if(map[i] == o && map[i+3] == o && map[i+6] == o){ return ow; }
            }
            //check for cross wins
            if(map[0] == x && map[4] == x && map[8] == x){ return xw; }
            if(map[0] == o && map[4] == o && map[8] == o){ return ow; }
            
            if(map[2] == x && map[4] == x && map[6] == x){ return xw; }
            if(map[2] == o && map[4] == o && map[6] == o){ return ow; }
            
            //check if cats game
            n = 8;
            int ret = -50;
            while(n != -1){ if(map[n] == s){ ret = 0; break; } n--; }
            
            return ret;
        }
        
        int minimax(char map[9], char depth, bool isMaxPlayer, char p, char e){
            int n = isDone(map);
            if(n == -50){
                return 0;
            } else if(n == -100){
                if(p == o){ n = -n; }
                return n + depth;
            } else if(n == 100){
                if(p == o){ n = -n; };
                return n - depth;
            }
            
            if(isMaxPlayer){
                int bestVal = -200;
                
                for(int i = 0; i < 9; i++){
                    if(map[i] == s){
                        map[i] = p;
                        n = minimax(map, depth+1, false, p, e);
                        bestVal = max(bestVal, n);
                        map[i] = s;
                    }
                }
                
                return bestVal;
            } else {
                int bestVal = 200;
                for(int i = 0; i < 9; i++){
                    if(map[i] == s){
                        map[i] = e;
                        n = minimax(map, depth+1, true, p, e);
                        bestVal = min(bestVal, n);
                        map[i] = s;
                    }
                }
                return bestVal;
            }
        }
        
    public:
        board(){
            s = '-', x = 'x', o = 'o';
            char i = 8;
            while(i != -1){ map[i] = s; i--; }
        }
        
        char& operator[](int in){
            return map[in];
        }
        
        int isDone(){
            char n = 0;
            for(int i = 0; i < 3; i++){
                //check for horizontal wins
                if(map[n] == x && map[n+1] == x && map[n+2] == x){ return 1; }
                if(map[n] == o && map[n+1] == o && map[n+2] == o){ return 2; }
                n += 3;
                
                //check for vertical wins
                if(map[i] == x && map[i+3] == x && map[i+6] == x){ return 1; }
                if(map[i] == o && map[i+3] == o && map[i+6] == o){ return 2; }
            }
            //check for cross wins
            if(map[0] == x && map[4] == x && map[8] == x){ return 1; }
            if(map[0] == o && map[4] == o && map[8] == o){ return 2; }
            
            if(map[2] == x && map[4] == x && map[6] == x){ return 1; }
            if(map[2] == o && map[4] == o && map[6] == o){ return 2; }
            
            //check if cats game
            n = 8;
            int ret = 3;
            while(n != -1){ if(map[n] == s){ ret = 0; break; } n--; }
            
            return ret;
        }
        
        void show(){
            int n = 0;
            for(int i = 0; i < 3; i++){
                printf("%c | %c | %c\n", map[n], map[n+1], map[n+2]);
                n += 3;
            }
            n = isDone();
            switch(n){
                case 1:
                    cout << "x wins" << endl; break;
                case 2:
                    cout << "o wins" << endl; break;
                case 3:
                    cout << "cat's game" << endl; break;
            }
        }
        
        int move(char player, char enemy){
            int bestMove = -1;
            int bestVal = -200;
            int n;
            for(int i = 0; i < 9; i++){
                if(map[i] == s){
                    map[i] = player;
                    n = minimax(map, 0, false, player, enemy);
                    if(n > bestVal){
                        bestVal = n;
                        bestMove = i;
                    }
                    map[i] = s;
                }
            }
            return bestMove;
        }
        
        void reset(){
            char n = 8;
            while(n != -1){ map[n] = s; n--; }
        }
};

#endif
