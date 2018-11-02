# Jellyfish 

This project is an assignement for the [MPRI course 2.39](https://wikimpri.dptinfo.ens-cachan.fr/doku.php?id=cours:c-2-39), it's aim is to modelise and animate jellyfishes. 

![The final result so far.](https://github.com/fnareoh/jellyfish/blob/master/final.gif)

Here is the final result rendered by povray.

You can find a small overview of the evolution of the project [here](http://fnareoh.net/jellyfish_anim/) and slides of the presentation [here](https://docs.google.com/presentation/d/1OcdV9GIDU5148Yyot86cO25l6Dp52UI90EFJqscVOrw/present?token=AC4w5VhrhGTgdf8ZD5iMh_7M71VzsYR7IA%3A1541159028710&includes_info_params=1#slide=id.p).

# Usage

```bash
# Render the final file `scene_frame_0.png`
make scene

# Make a quick rendering of the scene
make fast

# Make a slow rendering of the scene at higher resolution
make fancy

# Render the frame number i of the animation
make FRAME=i scene
```

You can also get the mesh as a standalone file:
```
FRAME=0  # frame to render (optional parameter)
SEED=0   # seed for rng (optional parameter)

make
./jellyfish pov $FRAME $SEED > jelly.pov
```

Where first parameter is the file format among:
 - pov/pov_mesh2: povray mesh2 format
 - pov_mesh: povray mesh format
 - stl

