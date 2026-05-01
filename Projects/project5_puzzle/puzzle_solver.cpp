#include "puzzle_solver.hpp"

void addFrameToGif(GifWriter &gif, const Puzzle &curr, int frame_duration)
{
  Image<Pixel> image = curr.toPicture();
  int gif_height = image.height();
  int gif_width = image.width();

  // 4 channels (RGBA)
  std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

  // convert the image to RGBA format for the GIF
  for (int r = 0; r < image.height(); ++r)
  {
    for (int c = 0; c < image.width(); ++c)
    {
      Pixel color = (image(r, c) == WHITE) ? Pixel{255, 255, 255} : Pixel{238, 142, 139};
      int index = (r * gif_width + c) * 4;
      rgb_data[index + 0] = color.red;
      rgb_data[index + 1] = color.green;
      rgb_data[index + 2] = color.blue;
      rgb_data[index + 3] = 255;
    }
  }

  GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // end addFrameToGif

void demoVisualize()
{
  Puzzle puzzle_default;
  GifWriter gif;
  Image<Pixel> img = puzzle_default.toPicture();
  int frame_duration = 100; // 100 centiseconds = 1 second
  GifBegin(&gif, "puzzle_solver_output.gif", img.width(), img.height(), frame_duration, 8, true);

  Puzzle puzzle;
  puzzle.fromString("123046758");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123406758");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123456708");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123456780");
  addFrameToGif(gif, puzzle, frame_duration);

  GifEnd(&gif);
} // end demoVisualize

PuzzleSolver::PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle)
    : initial(initialPuzzle), goal(goalPuzzle), solution_cost(0)
{
} // end constructor

int PuzzleSolver::getSolutionCost() const
{
  return solution_cost;
}

std::vector<std::string> PuzzleSolver::getSolutionPath() const
{
  std::vector<std::string> result;
  for (const Puzzle &p : solution_path)
    result.push_back(p.toString());
  return result;
}

bool PuzzleSolver::search()
{
  solution_cost = 0;
  solution_path.clear();
  // A* outline:
  // 1) Enqueue the initial Puzzle into frontier with:
  //      g = 0, h = initial.heuristic(goal), f = g + h.
  // 2) Keep a visited structure (hash-based is convenient for Puzzle).
  // 3) Dequeue (pop) the frontier entry with smallest f.
  //      From that node, read puzzle state and its g-cost.
  // 4) If current state is the goal, set solution_cost = current g-cost and return true.
  //      backtrace the solution via parent relationship into solution_path.
  // 5) Otherwise, generate neighbors in action order LEFT, RIGHT, UP, DOWN.
  // 6) For each valid neighbor:
  //      neighbor_g = current_g + 1
  //      neighbor_h = neighbor.heuristic(goal)
  //      use frontier contain method and visited structure to determine:
  //      - if not "seen" before, enqueue neighbor with g, h values, set up the parent relationship
  //      - if already in frontier with higher g, update that entry via replaceif, update the parent relationship if needed
  // 7) If frontier becomes empty, no solution is found: return false.

  //********************
  // set up the three main data structures we need for A*
  // frontier is our min-heap priority queue that always gives us the lowest f-cost state next
  // explored keeps track of states we already popped and expanded so we don't revisit them
  // parent maps each puzzle state to the state that came before it, so we can retrace our path at the end
  //********************
  frontier_queue<Puzzle> frontier;
  // explored is a visited stucture to keep track of explored states, so we don't revisit them and get stuck in loops
  std::unordered_set<Puzzle> explored;
  // parent is like the camefrom structure we used in project 4
  std::unordered_map<Puzzle, Puzzle> parent;
  
  //********************
  // push the initial state into the frontier with g=0 since we haven't moved yet
  // h is the manhattan distance from initial to goal
  //********************
  // enqueue the initial state into the frontier with g=0 and h=initial.heuristic(goal)
  frontier.push(initial, 0, initial.heuristic(goal));


  while (!frontier.empty())
  {
    //********************
    // pop the state with the lowest f-cost (g+h) from the frontier
    // this is the most the state we want to explore next
    // current_puzzle is the actual board configuration, current_gcost is how many moves we made to get here
    //********************

    // pop the state with the smallest f-cost from the frontier and get its puzzle state and g-cost
    State<Puzzle> current_state = frontier.pop();
    // current_puzzle is the puzzle state of the current state, and current_gcost is the g-cost to reach this state
    Puzzle current_puzzle = current_state.getValue();
    // get the g-cost to reach the current state
    int current_gcost = current_state.getPathCost();

    //********************
    // if the current state is the goal we found the shortest path
    // set solution_cost to the number of moves it took
    // then backtrace through the parent map from goal back to initial
    // insert at the front each time so the path ends up in the right order (initial to goal)
    // then generate the GIF by adding one frame per state in the solution path
    //********************
    if (current_puzzle == goal)
    {
      solution_cost = current_gcost;

      Puzzle p = current_puzzle;
      while (p != initial)
        {
          solution_path.insert(solution_path.begin(), p);
          p = parent[p];
        }
      solution_path.insert(solution_path.begin(), initial);

      // GIF generation
      // GifWriter gif;
      // Image<Pixel> img = initial.toPicture();
      // int frame_duration = 100;
      // GifBegin(&gif, "puzzle_solver_output.gif", img.width(), img.height(), frame_duration, 8, true);
      // for (const Puzzle &frame : solution_path)
      // {
      //   addFrameToGif(gif, frame, frame_duration);
      // }
      // GifEnd(&gif);

      return true;
    }
    //********************
    // mark the current state as explored so we dont look at its neighbors again
    //********************
    explored.insert(current_puzzle);

    //********************
    // try all four possible moves from the current state: LEFT, RIGHT, UP, DOWN
    // apply each action to get the neighbor state
    // skip it if the action wasn't valid (blank is at the edge)
    // skip it if we already explored it
    //********************
    for (Puzzle::Action a : {Puzzle::LEFT, Puzzle::RIGHT, Puzzle::UP, Puzzle::DOWN})
    {
      std::pair<bool, Puzzle> result = current_puzzle.apply(a);
      bool valid = result.first;
      Puzzle neighbor = result.second;
      if (!valid)
      {
        continue;
      }

      if (explored.count(neighbor))
      {
        continue;
      }

      //********************
      // neighbor_g is current moves + 1 since each move costs 1
      // neighbor_h is the manhattan distance from the neighbor to the goal
      // if the neighbor is unexplored, push it into the frontier and record its parent
      // if its already in the frontier but we found a cheaper path to it, update its cost with replaceif
      // and update the parent map so the path reconstruction will use the better route
      //********************
      int neighbor_g = current_gcost + 1;
      int neighbor_h = neighbor.heuristic(goal);

      if (!frontier.contains(neighbor))
      {
        frontier.push(neighbor, neighbor_g, neighbor_h);
        parent[neighbor] = current_puzzle;
      }
      else if (neighbor_g < frontier.getCurrentPathCost(neighbor))
      {
        frontier.replaceif(neighbor, neighbor_g);
        parent[neighbor] = current_puzzle;
      }
    }
  }
  //********************
  // if we emptied the frontier without finding the goal, no solution exists
  //********************
  return false;
}

