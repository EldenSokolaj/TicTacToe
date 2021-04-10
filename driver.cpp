#include "board.h"

int main(){
    srand(time(NULL));
    board game;
    int n;
    char p;
    while(true){
        printf("To move type [1-9]\nPlay as 'x', 'o', or none ('!')? ");
        cin >> p;
        system("clear");
        if(p == 'x'){
            while(!game.isDone()){
                game.show();
                cout << "?> ";
                cin >> n;
                if(game[n-1] != '-'){
                    printf("%d is an invalid move! Game aborted\n", n);
                    break;
                }
                game[n - 1] = p;
                game[game.move('o', 'x')] = 'o';
            }
        } else if(p == 'o'){
            while(!game.isDone()){
                game[game.move('x', 'o')] = 'x';
                if(game.isDone()){
                    break;
                }
                game.show();
                cout << "?> ";
                cin >> n;
                if(game[n-1] != '-'){
                    printf("%d is an invalid move! Game aborted\n", n);
                    break;
                }
                game[n - 1] = p;
            }
        } else {
            game[rand() * 100 % 9] = 'x';
            while(!game.isDone()){
                game.show();
                putchar('\n');
                game[game.move('o', 'x')] = 'o';
                if(game.isDone()){ break; }
                game.show();
                putchar('\n');
                game[game.move('x', 'o')] = 'x';
            }
        }
        game.show();
        printf("\n\n");
        game.reset();
    }
    return 0;
}
