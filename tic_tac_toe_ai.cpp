#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> computer_matrix(3, vector<int>(3));
vector<vector<char>> player_matrix(3, vector<char>(3));
map<vector<int>, int> mp_rows, mp_columns;
map<vector<int>, int> com_rows, com_columns;
map<vector<int>, int> mp_dia;
map<vector<int>, int> com_dia;

bool return_empty_space_row(int row){
    for(int i=0; i<3; i++){
        if(computer_matrix[row][i]==0){
            computer_matrix[row][i] = 1;
            com_rows[{0, row}]++;
            com_columns[{0, i}]++;
            player_matrix[row][i] = 'O';
            if(row==1 and i==1){
                com_dia[{0, 0}]++;
                com_dia[{0, 1}]++;
            }else if(row==i) com_dia[{0, 0}]++;
            else if((row+i)%2==0 and row!=i) com_dia[{0, 1}]++;
            mp_rows[{1, row}]=0;
            return true;
        }
    }
    return false;
}

bool return_empty_space_column(int col){
    for(int i=0; i<3; i++){
        if(computer_matrix[i][col]==0){
            computer_matrix[i][col] = 1;
            com_columns[{0, col}]++;
            com_rows[{0, i}]++;
            player_matrix[i][col] = 'O';
            if(col==1 and i==1){
                com_dia[{0, 0}]++;
                com_dia[{0, 1}]++;
            }else if(col==i) com_dia[{0, 0}]++;
            else if((col+i)%2==0 and col!=i) com_dia[{0, 1}]++;
            mp_columns[{1, col}] = 0;
            return true;
        }
    }
    return false;
}

int check_for_win_rows(){
    for(int i=0; i<3; i++){
        if(com_rows[{0, i}]==2){
            return i;
        }
    }
    return -1;
}

int check_for_win_cols(){
    for(int i=0; i<3; i++){
        if(com_columns[{0, i}]==2){
            return i;
        }
    }
    return -1;
}

int check_for_win_l_dia(){
    if(com_dia[{0, 0}]==2) return 0;
    else if(com_dia[{0, 1}]==2) return 1;
    else return -1;
}

void defend_algo(){
    int check_rows = check_for_win_rows();
    int check_cols = check_for_win_cols();
    int check_l_dia = check_for_win_l_dia();
    
    if(check_rows>=0){
        for(int i=0; i<3; i++){
            if(computer_matrix[check_rows][i]==0){
                computer_matrix[check_rows][i] = 1;
                player_matrix[check_rows][i] = 'O';
                com_rows[{0, check_rows}]++;
                return;
            }
        }
    }

    if(check_cols>=0){
        for(int i=0; i<3; i++){
            if(computer_matrix[i][check_cols]==0){
                computer_matrix[i][check_cols] = 1;
                player_matrix[i][check_cols] = 'O';
                com_columns[{0, check_cols}]++;
                return;
            }
        }
    }

    if(check_l_dia==0){
        if(computer_matrix[0][0]==0){
            computer_matrix[0][0] = 1;
            player_matrix[0][0] = 'O';
            com_rows[{0, 0}]++;
            com_columns[{0, 0}]++;
            com_dia[{0, 0}]++;
            return;
        }else if(computer_matrix[1][1]==0){
            computer_matrix[1][1] = 1;
            player_matrix[1][1] = 'O';
            com_rows[{0, 1}]++;
            com_columns[{0, 1}]++;
            com_dia[{0, 0}]++;
            return;
        }else if(computer_matrix[2][2]==0){
            computer_matrix[2][2] = 1;
            player_matrix[2][2] = 'O';
            com_rows[{0, 2}]++;
            com_dia[{0, 0}]++;
            com_columns[{0, 2}]++;
            return;
        }
    }else if(check_l_dia==1){
        if(computer_matrix[0][2]==0){
            computer_matrix[0][2] = 1;
            player_matrix[0][2] = 'O';
            com_rows[{0, 0}]++;
            com_columns[{0, 2}]++;
            com_dia[{0, 1}]++;
            return;
        }else if(computer_matrix[1][1]==0){
            computer_matrix[1][1] = 1;
            player_matrix[1][1] = 'O';
            com_rows[{0, 1}]++;
            com_columns[{0, 1}]++;
            com_dia[{0, 1}]++;
            return;
        }else if(computer_matrix[2][0]==0){
            computer_matrix[2][0] = 1;
            player_matrix[2][0] = 'O';
            com_rows[{0, 2}]++;
            com_dia[{0, 1}]++;
            com_columns[{0, 0}]++;
            return;
        }
    }

    for(int i=0; i<3; i++){
        if(mp_rows[{1, i}]==2){
            if(return_empty_space_row(i)){
                return;
            }
        }
    } 

    for(int i=0; i<3; i++){
        if(mp_columns[{1, i}]==2){
            if(return_empty_space_column(i)){
                return;
            }
        }
    }

    if(mp_dia[{0, 0}]==2){
        if(computer_matrix[0][0]==0){
            computer_matrix[0][0] = 1;
            com_dia[{0, 0}]++;
            com_columns[{0, 0}]++;
            com_rows[{0, 0}]++;
            player_matrix[0][0] = 'O';
            mp_dia[{0, 0}] = 0;
            return;
        }else if(computer_matrix[1][1]==0){
            computer_matrix[1][1] = 1;
            com_dia[{0, 0}]++;
            com_dia[{0, 1}]++;
            com_columns[{0, 1}]++;
            com_rows[{0, 1}]++;
            player_matrix[1][1] = 'O';
            mp_dia[{0, 0}] = 0;
            return;
        }else if(computer_matrix[2][2]==0){
            computer_matrix[2][2] = 1;
            com_dia[{0, 0}]++;
            com_columns[{0, 2}]++;
            com_rows[{0, 2}]++;
            player_matrix[2][2] = 'O';
            mp_dia[{0, 0}] = 0;
            return;
        }
    }

    if(mp_dia[{0, 1}]==2){
        if(computer_matrix[0][2]==0){
            computer_matrix[0][2] = 1;
            com_dia[{0, 1}]++;
            com_columns[{0, 2}]++;
            com_rows[{0, 0}]++;
            player_matrix[0][2] = 'O';
            mp_dia[{0, 1}] = 0;
            return;
        }else if(computer_matrix[1][1]==0){
            computer_matrix[1][1] = 1;
            com_dia[{0, 0}]++;
            com_dia[{0, 1}]++;
            com_columns[{0, 1}]++;
            com_rows[{0, 1}]++;
            player_matrix[1][1] = 'O';
            mp_dia[{0, 1}] = 0;
            return;
        }else if(computer_matrix[2][0]==0){
            computer_matrix[2][0] = 1;
            com_dia[{0, 1}]++;
            com_columns[{0, 0}]++;
            com_rows[{0, 2}]++;
            player_matrix[2][0] = 'O';
            mp_dia[{0, 1}] = 0;
            return;
        }
    }
    // If stalemate situation is occured

    for(int i=0; i<3; i++){
        if(com_rows[{0, i}]>=1){
            for(int j=0; j<3; j++){
                if(computer_matrix[i][j]==0){
                    computer_matrix[i][j] = 1;
                    player_matrix[i][j] = 'O';
                    com_rows[{0, i}]++;
                    return;
                }
            }
        }
    }

    for(int i=0; i<3; i++){
        if(com_columns[{0, i}]>=1){
            for(int j=0; j<3; j++){
                if(computer_matrix[j][i]==0){
                    computer_matrix[j][i] = 1;
                    player_matrix[j][i] = 'O';
                    com_columns[{0, i}]++;
                    return;
                }
            }
        }
    }

    // If nothing favours then chose an empty place

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(computer_matrix[j][i]==0){
                computer_matrix[j][i] = 1;
                player_matrix[j][i] = 'O';
                com_columns[{0, i}]++;
                com_rows[{0, j}]++;
                return;
            }
        }
    }
}

void first_move(int row, int col){
    if(row==col){
        if((row-1>=0 and col-1>=0) and computer_matrix[row-1][col-1]==0){
            computer_matrix[row-1][col-1] = 1;
            com_rows[{0, row-1}]++;
            com_columns[{0, col-1}]++;
            if(row-1==1 and col-1==1){
                com_dia[{0, 0}]++;
                com_dia[{0, 1}]++;
            }else{
                com_dia[{0, 0}]++;
            }
            player_matrix[row-1][col-1] = 'O';
        }else if((row+1<=3 and col+1<=3) and computer_matrix[row+1][col+1]==0){
            computer_matrix[row+1][col+1] = 1;
            com_rows[{0, row+1}]++;
            com_columns[{0, col+1}]++;
            if(row+1==1 and col+1==1){
                com_dia[{0, 0}]++;
                com_dia[{0, 1}]++;
            }else{
                com_dia[{0, 0}]++;
            }
            player_matrix[row+1][col+1] = 'O';
        }else if((row-1>=0 and col+1<=3) and computer_matrix[row-1][col+1]==0){
            computer_matrix[row-1][col+1] = 1;
            com_rows[{0, row-1}]++;
            com_columns[{0, col+1}]++;
            com_dia[{0, 1}]++;
            player_matrix[row-1][col+1] = 'O';
        }else if((row+1<=3 and col-1>=0) and computer_matrix[row+1][col-1]==0){
            computer_matrix[row+1][col-1] = 1;
            com_rows[{0, row+1}]++;
            com_columns[{0, col-1}]++;
            com_dia[{0, 1}]++;
            player_matrix[row+1][col-1] = 'O';
        }else{
            cout<<"Error!"<<endl;
        }
    }else{
        computer_matrix[1][1] = 1;
        com_rows[{0, 1}]++;
        com_columns[{0, 1}]++;
        com_dia[{0, 1}]++;
        com_dia[{0, 0}]++;
        player_matrix[1][1] = 'O';
    }
    return;
}

void print(){
    for(int i=0; i<3; i++){
        cout<<"|";
        for(int j=0; j<3; j++){
            if(player_matrix[i][j]==NULL or player_matrix[i][j]==' '){
                cout<<" ";
            }else{
                cout<<player_matrix[i][j];
            }
            cout<<"|";
        }
        cout<<endl;
    }
}

bool if_won_player(){
    for(int i=0; i<3; i++){
        if(mp_columns[{1, i}]==3 or mp_rows[{1, i}]==3 or mp_dia[{0, i}]==3){
            return true;
        }
    }
    return false;
}

bool if_won_computer(){
    for(int i=0; i<3; i++){
        if(com_columns[{0, i}]==3 or com_rows[{0, i}]==3 or com_dia[{0, i}]==3){
            return true;
        }
    }
    return false;
}

int main(){
    bool x = true;
    int first_step=1;
    print();
    cout<<"Use 1-indexed co-ordiantes."<<endl;
    cout<<"You are 'X'"<<endl;
    while(x){
        if(first_step==6){
            cout<<"DRAW!"<<endl;
            break;
        }
        int row, col;
        cin>>row>>col;
        player_matrix[row-1][col-1] = 'X';
        computer_matrix[row-1][col-1] = 2; // computer_matrix ---> player values
        mp_rows[{1, row-1}]++;
        mp_columns[{1, col-1}]++;
        if(row==2 and col==2){
            mp_dia[{0, 0}]++;
            mp_dia[{0, 1}]++;
        }else if((row+col)%2==0 and row==col){
            mp_dia[{0, 0}]++;
        }else if((row+col)%2==0 and row!=col){
            mp_dia[{0, 1}]++;
        }
        if(first_step==1){
            first_move(row-1, col-1);
        }else{
            defend_algo();
        }
        first_step++;
        print();
        if(if_won_player()){
            cout<<"Player has won!"<<endl;
            break;
        }else if(if_won_computer()){
            cout<<"Computer has won!"<<endl;
            break;
        }
    }
    return 0;
}
