#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"

emp::web::Document doc{"target"};
emp::Random random_2{5};
OrgWorld world{random_2};

class AEAnimator : public emp::web::Animate
{

    // grid width and height
    const int num_h_boxes = 20;
    const int num_w_boxes = 20;
    const double RECT_SIDE = 20;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    // where we'll draw
    emp::web::Canvas canvas{width, height, "canvas"};

public:
    AEAnimator()
    {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        world.Resize(10, 10);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        Organism *new_org_0 = new Organism(&random_2, 0, 1);
        Organism *new_org_1 = new Organism(&random_2, 0, 0);
        world.Inject(*new_org_0);
        world.Inject(*new_org_1);
    }

    void DoFrame() override
    {
        canvas.Clear();
        world.Update();

        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++)
        {
            for (int y = 0; y < num_h_boxes; y++)
            {
                if (world.IsOccupied(org_num))
                {
                    int species = world.GetOrg(org_num).GetSpecies();
                    if (species == 0)
                    {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "Red", "black");
                    }
                    if (species == 1)
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