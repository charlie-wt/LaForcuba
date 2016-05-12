# LaForcuba
Drawing 3D shapes on the LaFortuna board!


The program uses an interrupt-based timing system and functions from Steve Gunn's lcd library to draw points, lines and shapes in 3D space.

- Shapes are made up of lines, which are made up of points.
- Points are defined as a struct containing their current x, y and z coordinates, their previous x, y and z coordinates and their colour.
- Lines are defined as a struct containing two points. Their colour comes from their first point.
- Shapes are simply a list of lines.
- Points and lines are defined at the top of the file.
- Any transformations and redrawing are done in redraw(), in the main laforcuba.c file.
- Transformations should be applied first, then clearing the old shapes, then drawing the new ones, for maximum smoothness.

There are many different functions to draw points, lines and shapes:
	- draw_px: Located in laforcuba. Take sets of number coordinates. Built upon to abstract to 3D space.
	- draw_line: Located in laforcuba. Take sets of number coordinates. Built upon to abstract to 3D space.

	- draw_pt and clear_pt: Located in point. Take a point struct, which contains current coordinates, previous coordinates and colour.
	- draw_line_pt and clear_line_pt: Located in point. Take a point struct, and use it to draw a line.
	- clear_pt_p and clear_line_pt_p: Located in point. Clear the previous location of a point or line, using the display's background colour.
	- refresh_pt: Located in point. Takes a point struct, clears its previous location then draws it again in its new one.

	- draw_line_l: Located in line. Takes a line struct, which contains two points, and draws it.
	- clear_line_lp: Located in line. Clears the previous location of the line.
	- refresh_line: Located in line. Clears the line's previous location, then draws it in it's current location.
	- draw_shape: Located in line. Takes an undefined amount of lines, then draws them all.
	- clear_shape_p: Located in line. Takes an undefined amount of lines, then clears all their previous locations.
	- refresh_shape: Located in line. Takes an undefined amount of lines, then clears and redraws each one, one by one.
		- Note that because this function only clears one line at a time, it produces the smoothest results as well as using the least lines and so should be used when possible.
		- There is currently a bug with this function in that using display.background to clear the background produces incorect behaviour, and so a specific colour must be used.