# Assignment 1B
## Compilation
Use `make clean` to clean the directory of previously compiled materials. Then, use `make` to compile .o files and raytracer1b.

## Notes
I went to Simone's office hours on Friday 2/16 with an issue with example 5. For some reason, setting the view origin to `eye 0 0 10` makes it so that the spheres are too far away to be rendered. Setting it to `eye 0 0 1` has the spheres show back up, but the green sphere is rendered as an oval. Since Simone had many other students at his office hours, he wasn't able to spend much time with me and hence I was unable to debug this issue in time to turn in this assignment.

However, since example 5 demonstrates the rendering of shadows, Simone asked me to add a README that explained my situation and direct whichever TA is grading this assignment to look at the `showcase-att.png` to see correct rendering of shadows.

I run into the same problem with eye position in example 6. `showcase.png` and `showcase-att.png` both use multiple point lights, so they can be used to demonstrate how my program handles them.

## Pictures for Showcase
Images that should be included in the showcase presentation are `showcase-att.png` and `showcase-with-clipping.png`