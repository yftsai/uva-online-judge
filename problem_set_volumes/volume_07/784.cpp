#include <iostream>
#include <cstdlib>
using namespace std;

void paint(char maze[32][128], int m, int i, int j)
{
    if (i<0 || i>=m || j<0 || maze[i][j]=='\0')
        return;
    else if (maze[i][j]==' '){
        maze[i][j] = '#';
        paint(maze, m, i, j-1);
        paint(maze, m, i-1, j);
        paint(maze, m, i, j+1);
        paint(maze, m, i+1, j);
    }
}

int main()
{
    char line[128];
    char maze[32][128];
    int n;

    cin.getline(line, 128);
    n = atoi(line);

    for (n = atoi(line); n>0; n--){
        int m;
        for (m=0; ; m++){
            cin.getline(maze[m], 128);
            if (maze[m][0]=='_')
                break;
        }
        for (int i=0; i<m; i++){
            for (int j=0; maze[i][j]!='\0'; j++){
                if (maze[i][j]=='*'){
                    maze[i][j] = ' ';
                    paint(maze, m, i, j);
                }
            }
        }
        for (int i=0; i<=m; i++)
            cout << maze[i] << endl;
    }

    return 0;
}
