#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
// start  functions  defination
double **get_matrix(const int &row,const int &col);
void delete_mat(double **&ptr,const int &x);
void set_matrix(double**&mat,const int &row,const int &col);
void display(double**&mat,const int &row,const int &col);
void sum_mat(double**&a,const int &r1,const int &c1,double**&b,const int &r2,const int &c2);
void dif_mat(double**&a,const int &r1,const int &c1,double**&b,const int &r2,const int &c2);
void mult_mat(double**&a,const int &r1,const int &c1,double**&b,const int &r2,const int &c2);
double **get_mult_mat(double**&a,double**&b,const int &row,const int &col);
double **tran(double **&a, const int &r, const int &c) ;
double det(double**&a,const int &r);
double **adj(double**&a,const int &r);
double  **inverse(double **&mat,const int &r);
void solve(double**&a,double**&y ,const int &r);
void choice(char &ch);
void choice_data(char &ch);
void switch_a(double**&a,double**&temp,char &ch, int &r1, int &c1,bool &inner);
void switch_b(double**&b,double**&temp,char &ch, int &r2, int &c2,bool &inner);
void data(double**&a,double**&b,char &ch, int &r1, int &c1, int &r2, int &c2);
void general_switch(double**&A,double**&B,char &ch, int &r1, int &c1, int &r2, int &c2);
// end functions
// ========================================================
int main() {
    double **A ,**B;A=B= nullptr;
    int r1,c1,r2,c2;
    char ch;
    bool state =true;
    cout <<" Enter  m x n for matrix A \n";
    cin  >>r1 >> c1;
    A = get_matrix(r1,c1);
    set_matrix(A,r1,c1);
    cout <<" Enter  m x n for matrix B \n";
    cin >> r2 >> c2;
    B = get_matrix(r2,c2);
    set_matrix(B,r2,c2);
    while(true){
        choice(ch);
        general_switch(A,B,ch,r1,c1,r2,c2);
    }
    return 0;
}
//==========================================================================


// start function declaration
double **get_matrix(const int &row,const int &col){
    double **table =new double*[row];
    for(int i = 0 ; i < row ;  i++){
        *(table+i) = new double [col];
    }
    return table;
}
void delete_mat(double **&ptr,const int &x){
    for(int i = 0 ; i < x ; i++){
        delete[] ptr[i];
    }
    delete [] ptr;
    ptr = nullptr;
}
void set_matrix(double**&mat,const int &row,const int &col){
    cout << "Entering matrix : \n";
    for(int i =0 ; i < row ; i++){
        for(int j = 0 ;j < col  ; j++){
            cin >> mat[i][j];
        }
    }
}
void display(double**&mat,const int &row,const int &col){
    for(int i =0 ; i < row ; i++){
        for(int j = 0 ;j < col  ; j++){
            cout << mat[i][j]  <<" ";
        }
        cout << endl;
    }
}
void sum_mat(double**&a,const int &r1,const int &c1,double**&b,const int &r2,const int &c2){
    if(r1 !=r2 || c1 != c2){
        cout << "this operation is not valid\n";
        cout  << "rowA  must equals rowB and colA must equals colB\n";
    }else{
        double **c  = get_matrix(r1,c1);
        for(int i =0 ; i < r1; i++){
            for(int j =0 ; j < c1; j++){
                c[i][j] =  a[i][j] + b[i][j];
            }
        }
        cout << "the result of sum is : \n";
        display(c,r1,c1);
        delete_mat(c,r1);
    }
}
void dif_mat(double**&a,const int &r1,const int &c1,double**&b,const int &r2,const int &c2){
    if(r1 !=r2 || c1 != c2){
        cout << "this operation is not valid\n";
        cout  << "rowA  must equals rowB and colA must equals colB\n";
    }else{
        double **c  = get_matrix(r1,c1);
        for(int i =0 ; i < r1; i++){
            for(int j =0 ; j < c1; j++){
                c[i][j] =  a[i][j] - b[i][j];
            }
        }
        display(c,r1,c1);
        delete_mat(c,r1);
    }
}
void mult_mat(double**&a,const int &r1,const int &c1,double**&b,const int &r2,const int &c2){
    if(c1 !=r2){
        cout << "this operation is not valid\n";
        cout  << "colA  must equals rowB\n";
    }else{
        double **c  = get_matrix(r1,c2);
        double sum;
        for(int i =0 ; i < r1; i++){
            for(int j =0 ; j < c2; j++){
                sum = 0.0;
                for(int z= 0 ; z < c1 ; z++){
                    sum += a[i][z] * b[z][j];
                }
                c[i][j] =sum;
            }
        }
        cout << "the result of multiplication is : \n";
        display(c,r1,c2);
        delete_mat(c,r1);
    }
}
double **get_mult_mat(double**&a,double**&b,const int &row,const int &col){
        double **c  = get_matrix(row,col);
        double sum;
        for(int i =0 ; i < row; i++){
            for(int j =0 ; j < col; j++){
                sum = 0.0;
                for(int z= 0 ; z < row ; z++){
                    sum += (a[i][z] * b[z][j]);
                }
                c[i][j] =sum;
            }
        }
        return c;
}
double  **inverse(double **&mat,const int &r){
    double **inv = get_matrix(r,r);
    double determination = det(mat,r);
    if(determination == 0){
        cout << "cannot found inverse cause determination is zero\n";
        return nullptr;
    }
    inv = adj(mat,r);
    inv = tran(inv,r,r);
    for(int i = 0 ; i < r ; i++){
        for(int j = 0; j < r ; j++){
            inv[i][j] /= determination ;
        }
    }
    return inv;
}
double **adj(double**&a,const int &r){
    double**adj_A = get_matrix(r,r);
    for(int x =0 ; x <r ; x++){
        for(int y =0 ; y <r ; y++){
            double **sub_adj =  get_matrix(r-1,r-1);
            int sub_adj_i = 0;
            for(int i =0 ; i <r ; i++){
                if(x==i)
                    continue;
                int sub_adj_j = 0;
                for(int j = 0 ; j < r ; j++){
                    if( j == y)
                        continue;
                    sub_adj[sub_adj_i][sub_adj_j++] = a[i][j];

                }
                sub_adj_i++;
            }
            adj_A[x][y]  = pow(-1,x+y) * det(sub_adj,r-1);
            delete_mat(sub_adj,r-1);
        }
    }
    return adj_A;
}
double det(double**&a,const int &r){
    double determination=0.0;
    if(r==1)
        return a[0][0];
    if(r==2){
        return (a[0][0] * a[1][1] - a[1][0] * a[0][1]);
    }else{
        double **b = get_matrix(r-1,r-1);
        for(int x =0 ; x < r ;x++){
            int subi =0;
            for(int i=1 ; i < r ; i++){
                int subj=0;
                for(int j = 0 ; j < r ; j++){
                    if(j ==x)
                        continue;
                    b[subi][subj]= a[i][j];
                    subj++;
                }
                subi++;
            }
            determination += (pow(-1,x)* a[0][x] *det(b,r-1));
        }
        delete_mat(b,r-1);
        b= nullptr;
    }
    return determination;
}
void solve(double**&a,double**&y ,const int &r){
    double **inv =inverse(a,r);
    double **res = get_mult_mat(inv,y,r,1);
    for(int i = 0 ; i < r ; i++){
        cout << "X[" << i << "] = " << res[i][0] <<endl ;
    }
    delete_mat(res,r);
    delete_mat(inv,r);
}
void general_switch(double**&A,double**&B,char &ch, int &r1, int &c1, int &r2, int &c2){
    switch (tolower(ch)) {
        case'a':
            sum_mat(A,r1,c1,B,r2,c2);
            break;
        case 'b':
            cout << "A - B = \n";
            dif_mat(A,r1,c1,B,r2,c2);
            break;
        case 'c':
            cout << "B - A = \n";
            dif_mat(B,r2,c2,A,r1,c1);
            break;
        case'd':
            cout << "A * B = \n";
            mult_mat(A,r1,c1,B,r2,c2);
            break;
        case 'e':
            cout << "B * A = \n";
            mult_mat(B,r2,c2,A,r1,c1);
            break;
        case 'f':
            data(A,B,ch,r1,c1,r2,c2);
            break;
        case 'x':
            delete_mat(A,r1);
            delete_mat(B,r2);
            exit(0);
        default:
            cout << "option not found.........\n";
    }
}

double **tran(double **&a, const int &r, const int &c) {
    double **b = get_matrix(c, r);
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            b[i][j] = a[j][i];
        }
    }
    return b;
}
void choice(char &ch){
    cout << "[a] addition [A+B]\n";
    cout << "[b] difference [A-B]\n";
    cout << "[c] difference [B-A]\n";
    cout << "[d] multiply A * B\n";
    cout << "[e] multiply B * A\n";
    cout << "[f] opertions\n";
    cout << "[x] Exit\n";
    cout <<"___________\n";
    cout << "Choice: ";
    cin>> ch;
    cout << endl;
}
void choice_data(char &ch){
    cout << "[a]  display\n";
    cout << "[b]  modify\n";
    cout << "[c]  transpose\n";
    cout << "[d]  inverese\n";
    cout << "[e]  determination\n";
    cout << "[f]  solve eq\n";
    cout << "[x]  back\n";
    cout <<"___________\n";
    cout << "Choice: ";
    cin >> ch;
    cout << endl;
}
void switch_a(double**&a,double**&temp,char &ch, int &r1, int &c1,bool &inner){
    switch(tolower(ch)){
        case'a':
            display(a,r1,c1);
            break;
        case'b':
            delete_mat(a, r1);
            cout << "Enter new size: \n";
            cin >> r1 >> c1;
            temp = get_matrix(r1, c1);
            if (temp != nullptr) {
                a = temp;
                set_matrix(a, r1, c1);
                temp = nullptr;
            } else {
                cout << "Failed to allocate memory for the new matrix.\n";
            }
            break;
        case'c':
            temp = tran(a, r1, c1);
            if (temp != nullptr) {
                delete_mat(a, r1);
                swap(r1,c1);
                a = temp;
                delete_mat(temp, r1);

            } else {
                cout << "Transpose operation failed.\n";
            }
            break;
        case'd':
            if(r1 != c1){
                cout << "Dimension error \n";
                break;
            }
            temp = a;
            delete_mat(a,r1);
            a = inverse(temp,r1);
            delete_mat(temp ,r1);
            break;
        case'e':
            if(r1 == c1)
                cout << "determination = " <<det(a,r1);
            else
                cout << "cannot found determination \n";
            break;
        case 'f':
            cout <<"sovle equation AX=Y \n";
            cout << "enter matrix y :\n";
            temp = get_matrix(r1,1);
            set_matrix(temp,r1,1);
            solve(a,temp,r1);
            delete_mat(temp,r1);
            break;
        case'x':
            inner =false;
            break;
        default:
            cout << "option not found\n";
    }
}
void switch_b(double**&b,double**&temp,char &ch, int &r2, int &c2,bool &inner){
    switch (tolower(ch)) {
        case 'a':
            display(b, r2, c2);
            break;
        case 'b':
            delete_mat(b, r2);
            cout << "Enter new size: \n";
            cin >> r2 >> c2;
            temp = get_matrix(r2, c2);
            if (temp != nullptr) {
                b = temp;
                set_matrix(b, r2, c2);
                temp = nullptr;
            } else {
                cout << "Failed to allocate memory for the new matrix.\n";
            }
            break;
        case 'c':
            temp = tran(b, r2, c2);
            if (temp != nullptr) {
                delete_mat(b, r2);
                swap(r2, c2);
                b = temp;
                delete_mat(temp, r2);
            } else {
                cout << "Transpose operation failed.\n";
            }
            break;
        case 'd':
            if (r2 != c2) {
                cout << "Dimension error \n";
                break;
            }
            temp = b;
            delete_mat(b, r2);
            b = inverse(temp, r2);
            delete_mat(temp, r2);
            break;
        case 'e':
            if (r2 == c2)
                cout << "determination = " << det(b, r2);
            else
                cout << "cannot found determination \n";
            break;
        case 'f':
            cout <<"sovle equation BX=Y \n";
            cout << "enter matrix y :\n";
            temp = get_matrix(r2,1);
            set_matrix(temp,r2,1);
            solve(b,temp,r2);
            delete_mat(temp,r2);
            break;
        case 'x':
            inner = false;
            break;
        default:
            cout << "option not found\n";
    }
}
void data(double**&a,double**&b,char &ch, int &r1, int &c1, int &r2, int &c2){
    double** temp =nullptr;
    bool outer ,inner;
    outer =true;
    while(outer){
        inner =true;
        char A_B;
        cout << "\n[a] matrix A\n";
        cout << "[b] matrix B\n";
        cout <<  "pres any other key to back\n";
        cout <<"___________\n";
        cout << "Choice: ";
        cin>> A_B;
        while(inner){
            if(A_B =='a' || A_B == 'A'){
                cout << "\nMatrix A\n";
                choice_data(ch);
                switch_a(a,temp,ch,r1,c1,inner);
            }else if(A_B =='b' || A_B == 'B'){
                cout << "\nMatrix B\n";
                choice_data(ch);
                switch_b(b,temp,ch,r2,c2,inner);
            }else{
                outer =false;
                break;
            }
        }
    }
}