#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include "Graph.h"
#include "GraphOps.h"


using testing::Eq;

//=============================================================================
bool checkVectorIntAsArray(vector<int> res, vector<int> sol){
  if(res.size() != sol.size()){
    return false;
  }
  for (unsigned i = 0; i < res.size(); i++){
    if(sol[i] != res[i]){
      return false;
    }
  }
  return true;
}

//=============================================================================
bool checkVectorIntAsSet(vector<int> res, vector<int> sol){
  if(res.size() != sol.size()){
    return false;
  }
  for (unsigned i = 0; i < res.size(); i++){
    int item = sol[i];
    if(std::find(res.begin(), res.end(), item) == res.end()){
      return false;
    }
  }
  return true;
}




//=============================================================================
static Graph<int> graph1() {
   Graph<int> g;
   for (int i = 0; i <= 8; i++){
      g.addVertex(i);
   }

   g.addEdge(0,1,0);
   g.addEdge(0,2,0);
   g.addEdge(1,3,0);
   g.addEdge(2,3,0);
   g.addEdge(3,4,0);
   g.addEdge(4,5,0);
   g.addEdge(4,6,0);
   g.addEdge(5,8,0);
   g.addEdge(6,7,0);

   return g;
}

static  Graph<int> graph2() {
   Graph<int> g;
   for (int i = 0; i <= 8; i++){
      g.addVertex(i);
   }

   g.addEdge(0,1,0);
   g.addEdge(0,2,0);
   g.addEdge(1,2,0);
   g.addEdge(3,4,0);
   g.addEdge(5,8,0);
   g.addEdge(5,6,0);
   g.addEdge(7,6,0);
   g.addEdge(7,8,0);

   return g;
}

static  Graph<int> graph3() {
   Graph<int> g;
   for (int i = 0; i <= 11; i++){
      g.addVertex(i);
   }

   g.addEdge(0,1,0);
   g.addEdge(1,2,0);
   g.addEdge(2,3,0);
   g.addEdge(0,6,0);
   g.addEdge(1,7,0);
   g.addEdge(3,8,0);
   g.addEdge(6,2,0);
   g.addEdge(7,8,0);
   g.addEdge(4,5,0);
   g.addEdge(4,10,0);
   g.addEdge(4,11,0);
   g.addEdge(5,9,0);
   g.addEdge(5,11,0);
   g.addEdge(11,10,0);
   g.addEdge(10,5,0);

   return g;
}


//=============================================================================
// TEST 1
//=============================================================================

TEST(test_1, unconnected) {
    Graph<int> g1;
    Graph<int> g2;
    Graph<int> g3;
    bool res;

    g1 = graph1();
    res =  GraphOps::directlyUnconnected(g1, 1, 2); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g1, 1, 3); EXPECT_EQ(res, 0);
    res =  GraphOps::directlyUnconnected(g1, 3, 1); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g1, 2, 0); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g1, 0, 4); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g1, 3, 4); EXPECT_EQ(res, 0);

    g2 = graph2();
    res =  GraphOps::directlyUnconnected(g2, 1, 2); EXPECT_EQ(res, 0);
    res =  GraphOps::directlyUnconnected(g2, 1, 3); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g2, 3, 1); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g2, 2, 0); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g2, 0, 4); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g2, 3, 4); EXPECT_EQ(res, 0);

    g3 = graph3();
    res =  GraphOps::directlyUnconnected(g3, 1, 2); EXPECT_EQ(res, 0);
    res =  GraphOps::directlyUnconnected(g3, 1, 3); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g3, 3, 1); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g3, 2, 0); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g3, 0, 4); EXPECT_EQ(res, 1);
    res =  GraphOps::directlyUnconnected(g3, 3, 4); EXPECT_EQ(res, 1);
}

//=============================================================================
// TEST 2 
//=============================================================================

TEST(test_2, largestOutDegree) {
  vector<int> vec1;
  vector<int> vec2;
  vector<int> vec3;
  vector<int> sol1;
  vector<int> sol2;
  vector<int> sol3;
  Graph<int> g1;
  Graph<int> g2;
  Graph<int> g3;
  bool res;

  g1 = graph1();
  sol1 = {0,4};
  vec1 = GraphOps::largestOutDegree(g1);
  res = checkVectorIntAsSet(vec1, sol1);
  EXPECT_EQ(res,true);

  g2 = graph2();
  sol2 = {0, 5, 7};
  vec2 = GraphOps::largestOutDegree(g2);
  res = checkVectorIntAsSet(vec2, sol2);
  EXPECT_EQ(res,true);

  g3 = graph3();
  sol3 = {4};
  vec3 = GraphOps::largestOutDegree(g3);
  res = checkVectorIntAsSet(vec3, sol3);
  EXPECT_EQ(res,true);
}

//=============================================================================
// TEST 3 
//=============================================================================
TEST(test_3, isDAG) {
  Graph<int> g1;
  Graph<int> g2;
  Graph<int> g3;
  bool res;

  g1 = graph1();
  res = GraphOps::isDAG(g1);
  EXPECT_EQ(res,1);

  g2 = graph2();
  res = GraphOps::isDAG(g2);
  EXPECT_EQ(res,1);

  g3 = graph3();
  res = GraphOps::isDAG(g3);
  EXPECT_EQ(res,0);
}

//=============================================================================
// TEST 4 
//=============================================================================
TEST(test_4, numberSourcesSinks) {
  vector<int> vec1;
  vector<int> vec2;
  vector<int> vec3;
  vector<int> sol1;
  vector<int> sol2;
  vector<int> sol3;
  Graph<int> g1;
  Graph<int> g2;
  Graph<int> g3;
  bool res;

  g1 = graph1();
  sol1 = {2, 1};
  vec1 = GraphOps::numberSourcesSinks(g1);
  res = checkVectorIntAsArray(vec1, sol1);
  EXPECT_EQ(res,true);

  g2 = graph2();
  sol2 = {4, 4};
  vec2 = GraphOps::numberSourcesSinks(g2);
  res = checkVectorIntAsArray(vec2, sol2);
  EXPECT_EQ(res,true);

  g3 = graph3();
  sol3 = {2, 2};
  vec3 = GraphOps::numberSourcesSinks(g3);
  res = checkVectorIntAsArray(vec3, sol3);
  EXPECT_EQ(res,true);
}

//=============================================================================
// TEST 5 
//=============================================================================
TEST(test_5, pathExists){
  Graph<int> g1;
  Graph<int> g2;
  Graph<int> g3;
  vector<int> skip1;
  vector<int> skip2;
  vector<int> skip3;
  int res;

  skip1.push_back(2);
  skip2.push_back(3);
  skip3.push_back(4);

  g1 = graph1();
  res = GraphOps::pathExists(g1, 0, 5, skip1); EXPECT_EQ(res,1);
  res = GraphOps::pathExists(g1, 0, 5, skip2); EXPECT_EQ(res,0);
  res = GraphOps::pathExists(g1, 1, 6, skip3); EXPECT_EQ(res,0);

  g2 = graph2();
  res = GraphOps::pathExists(g2, 0, 5, skip1); EXPECT_EQ(res,0);
  res = GraphOps::pathExists(g2, 0, 5, skip2); EXPECT_EQ(res,0);
  res = GraphOps::pathExists(g2, 1, 6, skip3); EXPECT_EQ(res,0);

  g3 = graph3();
  res = GraphOps::pathExists(g3, 0, 5, skip1); EXPECT_EQ(res,0);
  res = GraphOps::pathExists(g3, 0, 5, skip2); EXPECT_EQ(res,0);
  res = GraphOps::pathExists(g3, 1, 6, skip3); EXPECT_EQ(res,0);
}

//=============================================================================
// TEST 6 
//=============================================================================
TEST(test_6, numberComponents){
  Graph<int> g1;
  Graph<int> g2;
  Graph<int> g3;
  int res;

  g1 = graph1();
  res =  GraphOps::numberConnectedComponents(g1); EXPECT_EQ(res,1);
  g2 = graph2();
  res =  GraphOps::numberConnectedComponents(g2); EXPECT_EQ(res,3);
  g3 = graph3();
  res =  GraphOps::numberConnectedComponents(g3); EXPECT_EQ(res,2);
}
