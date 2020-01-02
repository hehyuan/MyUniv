#include"Park.h"
Park::Park(){
    //init park
    initAll();
};

 string Park::queryEmptyPos(int flag){
     string ans="";
//     for(int i =0;i<PosRow;++i){
//         for(int j =0;j<PosCol;++j){
//             if(p[i][j].isValid()&&p[i][j].getFlag()==flag){
//                    ans += "("+to_string(i)+","+to_string(j)+")\n";
//             }
//         }
//     }
     if(ans.empty()==true)return "false";
     else return ans;
}

Position** Park::initAll(){
    Position **ptr = NULL;
     for(int i = 0;i<PosRow;++i){
         for(int j = 0;j<PosCol;++j){
             ptr[i][j] = *new Position(i,j,1);
         }
     }
     return ptr;
 }
