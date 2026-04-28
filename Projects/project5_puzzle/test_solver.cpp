#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <chrono>

#include "puzzle_solver.hpp"

/* Frontier queue tests start here*/
TEST_CASE("Simple push and pop test", "[frontier_queue]")
{
  frontier_queue<char> fq;
  REQUIRE(fq.empty());
  fq.push('A', 0, 1);
  REQUIRE_FALSE(fq.empty());
  REQUIRE(fq.contains('A'));

  frontier_queue<char> fq2;
  fq2.push('B', 1, 1);
  State<char> state = fq2.pop();
  REQUIRE(state.getValue() == 'B');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 2);
  REQUIRE(fq2.empty());
}

TEST_CASE("Simple contains and replaceif test", "[frontier_queue]")
{
  frontier_queue<char> fq;
  REQUIRE_FALSE(fq.contains('A'));
  REQUIRE_FALSE(fq.contains('B'));
  fq.push('A', 1, 1);
  fq.push('B', 2, 2);
  REQUIRE(fq.contains('A'));
  REQUIRE(fq.contains('B'));
  REQUIRE_FALSE(fq.contains('C'));

  frontier_queue<char> fq2;
  fq2.push('A', 100, 100);
  fq2.replaceif('A', 1);
  State<char> state = fq2.pop();
  REQUIRE(state.getValue() == 'A');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 101);

  frontier_queue<char> fq3;
  fq3.push('A', 1, 100);
  fq3.replaceif('A', 50);
  State<char> state2 = fq3.pop();
  REQUIRE(state2.getPathCost() == 1);
}

/* Puzzle tests start here*/
TEST_CASE("Simple hash test", "[puzzle]")
{
  Puzzle p1, p2, p3;
  p1.fromString("876543210");
  p2.fromString("012345678");
  p3.fromString("102345678");
  REQUIRE(p2.hash() == 305419896ULL);
  REQUIRE(p1.hash() != p3.hash());
}

TEST_CASE("Simple operator== and operator!= test", "[puzzle]")
{
  Puzzle p1, p2, p3;
  p1.fromString("012345678");
  p2.fromString("012345678");
  p3.fromString("102345678");
  REQUIRE(p1 == p2);
  REQUIRE_FALSE(p1 == p3);
  REQUIRE(p1 != p3);
  REQUIRE_FALSE(p1 != p2);
}

TEST_CASE("Simple heuristic test", "[puzzle]")
{
  Puzzle goal, p1, p2, p3;
  goal.fromString("012345678");
  p1.fromString("012345678");
  p2.fromString("102345678");
  p3.fromString("120345678");
  REQUIRE(p1.heuristic(goal) == 0);
  REQUIRE(p2.heuristic(goal) == 1);
  REQUIRE(p3.heuristic(goal) == 2);
}

/* Puzzle solver tests start here*/
TEST_CASE("Simple search test cost 0", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("123456780"));
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 0);
    REQUIRE(solver.getSolutionPath().size() == 1);
  }
  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 0);
    REQUIRE(solver.getSolutionPath().size() == 1);
  }
}

TEST_CASE("Simple search test cost 1", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456708")); // blank at (2,1) — one RIGHT from goal
  REQUIRE(puzzle2.fromString("123456780")); // blank at (2,2) — goal
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 1);
    REQUIRE(solver.getSolutionPath().size() == 2);
    std::vector<std::string> expected_path = {"123456708", "123456780"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 1);
    REQUIRE(solver.getSolutionPath().size() == 2);
    std::vector<std::string> expected_path = {"123456780", "123456708"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
}

TEST_CASE("Simple search test cost 2", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456078")); // blank at (2,0) — two RIGHTs from goal
  REQUIRE(puzzle2.fromString("123456780")); // blank at (2,2) — goal
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    REQUIRE(solver.getSolutionPath().size() == 3);
    std::vector<std::string> expected_path = {"123456078", "123456708", "123456780"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    REQUIRE(solver.getSolutionPath().size() == 3);
    std::vector<std::string> expected_path = {"123456780", "123456708", "123456078"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
}

/** Two time-consuming tests are given here for your reference. Uncomment them to try locally.
 * The test case of cost 31 should execute within 1 minute locally to avoid timeout on the autograder.*/


TEST_CASE("Time-consuming search test cost 8", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("012563478"));
  REQUIRE(puzzle1 != puzzle2);
  REQUIRE(puzzle1.heuristic(puzzle2) == 8);

  PuzzleSolver solver(puzzle2, puzzle1);
  REQUIRE(solver.search());
  REQUIRE(solver.getSolutionCost() == 8);
  Puzzle curr = puzzle2;
  int remaining = 8;
  std::vector<Puzzle::Action> actions = {Puzzle::RIGHT, Puzzle::RIGHT, Puzzle::DOWN, Puzzle::LEFT, Puzzle::LEFT, Puzzle::DOWN, Puzzle::RIGHT, Puzzle::RIGHT};
  for (const auto &a : actions)
  {
    std::pair<bool, Puzzle> result = curr.apply(a);
    REQUIRE(result.first);
    curr = result.second;
    remaining -= 1;
    PuzzleSolver inner(curr, puzzle1);
    REQUIRE(inner.search());
    REQUIRE(inner.getSolutionCost() == remaining);
    REQUIRE(curr.heuristic(puzzle1) <= inner.getSolutionCost());
  }
  REQUIRE(curr == puzzle1);
}

TEST_CASE("Time-consuming search test cost 31", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("867254301"));
  PuzzleSolver solver(puzzle2, puzzle1);
  auto start = std::chrono::high_resolution_clock::now();
  REQUIRE(solver.search());
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  REQUIRE(solver.getSolutionCost() == 31);
  std::cout << "\n**********************************************************\n"
            << std::endl;
  std::cout << "Time taken to find solutions in the hardest puzzle: " << elapsed.count() << " seconds" << std::endl;
  std::cout << "\n**********************************************************\n"
            << std::endl;
}


// You still need to write your own unit test
// Test 1: heuristic returns 0 when puzzle equals goal
// in plain english, this test checks that if we have a puzzle state p1 and a goal state p2,
// and if p1 is the same as p2 (they represent the same board configuration),
// then the heuristic value of p1 with respect to p2 should be 0, which means that
// there are no misplaced tiles and p1 is already at the goal state
TEST_CASE("Heuristic returns 0 when puzzle equals goal", "[puzzle]")
{
  Puzzle p1, p2;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("123456780"));
  REQUIRE(p1.heuristic(p2) == 0);
}
// Test 2: heuristic is always <= actual solution cost (admissibility)
// in plain english, this test checks that for any two puzzle states p1 and p2,
// the heuristic value of p1 with respect to p2 should always be less than or equal to the actual solution cost
// to get from p1 to p2, which ensures that the heuristic is admissible and
// does not overestimate the true cost of reaching the goal state from any given state
TEST_CASE("Heuristic is always <= actual solution cost", "[puzzle]")
{
  Puzzle p1, p2;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("012345678"));
  PuzzleSolver solver(p2, p1);
  REQUIRE(solver.search());
  REQUIRE(p2.heuristic(p1) <= solver.getSolutionCost());
}
// Test 3: search returns false for unsolvable puzzle
// in plain english, this test checks that if we have an unsolvable puzzle
// (a puzzle configuration that cannot be transformed into the goal
// configuration through any sequence of valid moves), then the search function
// should return false, indicating that no solution exists for that puzzle
TEST_CASE("Search returns false for unsolvable puzzle", "[PuzzleSolver]")
{
  Puzzle p1, p2;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("123456870")); // swap of 8 and 7 makes it unsolvable
  PuzzleSolver solver(p2, p1);
  REQUIRE_FALSE(solver.search());
}
// Test 4: solution path starts with initial and ends with goal
// in plain english, this test checks that the first state in the solution path
// is the initial state, and the last state in the solution path is the goal state,
// which makes sure that the solution path correctly shows a valid sequence of
// moves from the initial state to the goal state
TEST_CASE("Solution path starts with initial and ends with goal", "[PuzzleSolver]")
{
  Puzzle p1, p2;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("123456870")); // swap of 8 and 7 makes it unsolvable
  PuzzleSolver solver(p2, p1);
  REQUIRE_FALSE(solver.search());
}
// Test 4: solution path starts with initial and ends with goal
// in plain english, this test checks that the first state in the solution path
// is the initial state, and the last state in the solution path is the goal state,
// which ensures that the solution path correctly represents a valid sequence of
// moves from the initial state to the goal state
TEST_CASE("Solution path starts with initial and ends with goal", "[PuzzleSolver]")
{
  Puzzle p1, p2;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("012345678"));
  PuzzleSolver solver(p2, p1);
  REQUIRE(solver.search());
  std::vector<std::string> path = solver.getSolutionPath();
  REQUIRE(path.front() == "012345678");
  REQUIRE(path.back() == "123456780");
}
// Test 5: each consecutive state in solution path differs by exactly one move
// in plain english, this test checks that for each pair of consecutive states in
// the solution path, they should differ by exactly one valid move (one tile moved
// into the blank space), which ensures that the solution path is a valid sequence of moves
// from the initial state to the goal state
TEST_CASE("Each consecutive state in solution path differs by exactly one move", "[PuzzleSolver]")
{
  Puzzle p1, p2;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("123456870")); // swap of 8 and 7 makes it unsolvable
  PuzzleSolver solver(p2, p1);
  REQUIRE_FALSE(solver.search());
}
// Test 6: hash produces different values for every unique board configuration
// in plain english, this test checks that if we have three different board configurations,
// then their hash values should all be different, which means that the hash function
// is distinguishing between different puzzle states
TEST_CASE("Hash produces different values for every unique board configuration", "[puzzle]")
{
  Puzzle p1, p2, p3;
  REQUIRE(p1.fromString("123456780"));
  REQUIRE(p2.fromString("123456708"));
  REQUIRE(p3.fromString("123456078"));
  REQUIRE(p1.hash() != p2.hash());
  REQUIRE(p1.hash() != p3.hash());
  REQUIRE(p2.hash() != p3.hash());
}
// Test 7: replaceif does not update when new cost is higher than existing cost
// in plain english, this test checks that if we call replaceif with a new cost that
// is higher than the existing cost of the state in the frontier, then the frontier
// should not update the path cost or f-cost of that state, and should not change
// its position in the min-heap order of the frontier
TEST_CASE("replaceif does not update when new cost is higher than existing cost", "[frontier_queue]")
{
  frontier_queue<char> fq;
  fq.push('A', 1, 1); // f = 2
  fq.replaceif('A', 2); // new g = 2, new f = 3, which is higher than existing f = 2, so should not update
  State<char> state = fq.pop();
  REQUIRE(state.getValue() == 'A');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 2);
}
// Test 8: frontier pop always returns states in non-decreasing f-cost order
// in plain english, this test checks that the frontier always pops the state
// with the lowest f-cost, and that the f-cost of popped states never decreases (it can stay the same or increase, but not decrease)
TEST_CASE("Frontier pop always returns states in non-decreasing f-cost order", "[frontier_queue]")
{
  frontier_queue<char> fq;
  fq.push('A', 1, 1); // f = 2
  fq.push('B', 2, 2); // f = 4
  fq.push('C', 0, 3); // f = 3
  State<char> state1 = fq.pop();
  REQUIRE(state1.getValue() == 'A');
  REQUIRE(state1.getFCost() == 2);
  State<char> state2 = fq.pop();
  REQUIRE(state2.getValue() == 'C');
  REQUIRE(state2.getFCost() == 3);
  State<char> state3 = fq.pop();
  REQUIRE(state3.getValue() == 'B');
  REQUIRE(state3.getFCost() == 4);
}