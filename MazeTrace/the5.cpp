#include "the5.h"

/* 
    in the5.h "struct Room" is defined as below:
    
    struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

*/


vector<int> maze_trace(vector<Room*> maze) { 

    vector<int> path;
        
    stack<Room*> roomStack;

    vector<Room*> visitedRooms;

    roomStack.push(maze[0]);

    stack<Room*> backtrackStack;

    while(!roomStack.empty()){

        Room* currentRoom = roomStack.top();
        roomStack.pop();

        bool isVisited = false;
        for(int j = 0; j < visitedRooms.size(); j++){
            if(visitedRooms[j]->id == currentRoom->id){
                isVisited = true;
                break;
            }
        }
        if(isVisited)
            continue;

        
        visitedRooms.push_back(currentRoom);


        if(currentRoom->content == '*'){

            path.push_back(currentRoom->id);
            while(!backtrackStack.empty()){
                Room* top = backtrackStack.top();
                path.push_back(top->id);
                backtrackStack.pop();
                
            }
            if(path[path.size()-1] != maze[0]->id){
                path.push_back(maze[0]->id);
            }
            break;
        }

        else{
            path.push_back(currentRoom->id);

            bool isDeadEnd = true;
            for(int i = 0; i < currentRoom->neighbors.size(); i++){
                Room* neighbor = currentRoom->neighbors[i];
                bool isVisited = false;
                for(int j = 0; j < visitedRooms.size(); j++){
                    if(visitedRooms[j]->id == neighbor->id){
                        isVisited = true;
                        break;
                    }
                }
                if(!isVisited){
                    isDeadEnd = false;
                    break;
                }
            }
            if(currentRoom->neighbors.size() != 1 && !isDeadEnd){
                backtrackStack.push(currentRoom);
            }
            else{
                while(!backtrackStack.empty()){
                    Room* top = backtrackStack.top();
                    bool allVisited = true;
                    for(int i = 0; i < top->neighbors.size(); i++){
                        bool isVisited = false;
                        for(int j = 0; j < visitedRooms.size(); j++){
                            if(visitedRooms[j]->id == top->neighbors[i]->id){
                                isVisited = true;
                                break;
                            }
                        }
                        if(!isVisited){
                            allVisited = false;
                            break;
                        }
                    }
                    if(allVisited){
                        path.push_back(top->id);
                        backtrackStack.pop();
                    }
                    else{
                        path.push_back(top->id);
                        break;
                    }
                }
            }
            
            for(int i = currentRoom->neighbors.size() - 1; i >= 0 ; i--){
                Room* neighbor = currentRoom->neighbors[i];
                bool isVisited = false;
                for(int j = 0; j < visitedRooms.size(); j++){
                    if(visitedRooms[j]->id == neighbor->id){
                        isVisited = true;
                        break;
                    }
                }
                if(!isVisited){
                    roomStack.push(neighbor);
                }

            }
        }
    }
    

    return path; 
}


