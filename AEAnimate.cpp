#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"

// Initialize variables

emp::web::Document doc{"target"};
emp::Random random_2{5};
emp::Random random_1{30};
OrgWorld world{random_2};

class AEAnimator : public emp::web::Animate
{

    // Grid width and height
    const int num_h_boxes = 20;
    const int num_w_boxes = 20;
    const double RECT_SIDE = 20;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    // Canvas where we'll draw
    emp::web::Canvas canvas{width, height, "canvas"};

public:
    AEAnimator()
    {
        // Set up Buttons and Put text on webpage
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        doc << "<h2>Welcome to the Simulation!</h2>";
        doc << "<p>Green boxes represent grass, and Blue represent cows</p>";
        doc << "<p>Grass grows every 10 steps</p>";
        doc << "<p>Cows move to eat grass. If they go too long without eating grass, they die!</p>";

        // Set up world
        world.Resize(10, 10);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        // Inject our organisms. First Grass
        for (int i = 0; i < 30; ++i)
        {
            int pos = random_2.GetUInt(world.GetSize());
            world.AddOrgAt(emp::NewPtr<Grass>(&random_2), pos);
        }
        // Then Cows
        for (int i = 0; i < 5; ++i)
        {
            int pos = random_2.GetUInt(world.GetSize());
            world.AddOrgAt(emp::NewPtr<Cow>(&random_2), pos);
        }
    }

    // Draw the Canvas and Grid
    void DoFrame() override
    {
        canvas.Clear();
        world.Update();

        int org_num = 0;
        // Draw the grid
        for (int x = 0; x < num_w_boxes; x++)
        {
            for (int y = 0; y < num_h_boxes; y++)
            {
                if (world.IsOccupied(org_num))
                {
                    int species = world.GetOrg(org_num).GetSpecies();
                    if (species == 0) // grass
                    {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "Green", "black");
                    }
                    if (species == 1) // cow
                    {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "Blue", "black");
                    }
                }
                else
                {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main()
{
    animator.Step();
}