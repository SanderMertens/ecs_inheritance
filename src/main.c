#include <ecs_inheritance.h>

/* This system only matches with the square_base entity */
void AnimateSquare(ecs_rows_t *rows) {
    ECS_COLUMN(rows, EcsSquare, square, 1);

    /* Iterates only once */
    for (int i = 0; i < rows->count; i ++) {
        square[i].size = sin(rows->world_time * 1.8) * 30.0 + 35;
    }
}

/* This system only matches with the shape_base entity */
void AnimateColor(ecs_rows_t *rows) {
    ECS_COLUMN(rows, EcsColor, color, 1);

    /* Iterates only once */
    for (int i = 0; i < rows->count; i ++) {
        color[i].r = ((cos(rows->world_time / 1.5) + 1) / 2) * 255.0;
        color[i].b = 200;
        color[i].g = ((sin(rows->world_time / 1.5) + 1) / 2) * 255.0;
    }
}

int main(int argc, char *argv[]) {
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_IMPORT(world, FlecsComponentsTransform, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsGeometry, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsGraphics, ECS_2D);
    ECS_IMPORT(world, FlecsSystemsSdl2, ECS_2D);

    /* Create a base shape entity that just has a color */
    ecs_entity_t shape_base = ecs_set(world, 0, EcsColor, {.r = 0, .g = 0, .b = 255, .a = 255});
    /* Add EcsDisabled so the entity won't be matched with normal systems */
    ecs_add(world, shape_base, EcsDisabled);

    /* Create a base entity for squares */
    ecs_entity_t square_base = ecs_set(world, 0, EcsSquare, {.size = 10});
    /* The square_base inherits from shape_base */
    ecs_inherit(world, square_base, shape_base);
    /* Add EcsDisabled so the entity won't be matched with normal systems */
    ecs_add(world, square_base, EcsDisabled);

    /* Create 100 instances of square */
    for (int x = 0; x < 10; x ++) {
        for (int y = 0; y < 10; y ++) {
            ecs_entity_t e = ecs_new_instance(world, square_base, EcsPosition2D);
            ecs_set(world, e, EcsPosition2D, {(x - 4.5) * 30, (y - 4.5) * 30});
        }
    }

    /* Create 3 squares that override size */
    for (int y = 0; y < 3; y ++) {
        ecs_entity_t e = ecs_new_instance(world, square_base, EcsPosition2D);
        ecs_set(world, e, EcsPosition2D, {-300, (y - 1) * 100});
        ecs_set(world, e, EcsSquare, {.size = y * 20 + 20});
    }

    /* Create 3 squares that inherit from shape_base */
    for (int y = 0; y < 3; y ++) {
        ecs_entity_t e = ecs_new_instance(world, shape_base, EcsPosition2D);
        ecs_set(world, e, EcsPosition2D, {300, (y - 1) * 100});
        ecs_set(world, e, EcsCircle, {.radius = y * 10 + 10});
    }

    /* Define systems that animates size and color. Add EcsDisabled so the 
     * system only matches disabled entities (square_base). */
    ECS_SYSTEM(world, AnimateSquare, EcsOnUpdate, EcsSquare, EcsDisabled);
    ECS_SYSTEM(world, AnimateColor, EcsOnUpdate, EcsColor, EcsDisabled);

    /* Initialize canvas */
    ecs_set(world, 0, EcsCanvas2D, {
        .window = { .width = 800, .height = 600 }, .title = "Hello ecs_inheritance!" 
    });

    /* Enter main loop */
    ecs_set_target_fps(world, 60);

    while ( ecs_progress(world, 0));

    /* Cleanup */
    return ecs_fini(world);
}
