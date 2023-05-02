# Koch graph

Program that rapresent Koch curve and Koch snowflake.

### Usage: `py Koch_graph.py`

To download the lastest release you can click [here](https://github.com/Filippo2903/Koch-Curve/releases/latest).

## Examples
### Curve with 5 iteration
<img src="https://user-images.githubusercontent.com/107002401/235722138-f532fdb2-8a1c-4f4a-9362-271d393e9838.png" alt="Koch curve" width=500 />

### Snowflake with 6 iteration
<img src="https://user-images.githubusercontent.com/107002401/235722252-fc92a61e-173b-41e0-aceb-8cd0d87af5bd.png" alt="Koch snowflake" width=500 />

## Run
```bash
$ py Koch_graph.py
```

## How to use it
After running the program, it will appear a window where you can set the points among which the graph will be plotted and the iteretion count.

<img src="https://user-images.githubusercontent.com/107002401/235721870-20fe5be7-cc40-4930-ab48-dd903b07c9fa.png" alt="Set coords window" width=200 />

You can choose the Koch curve or the Koch snowflake using the drop down menu.

<img src="https://user-images.githubusercontent.com/107002401/235721987-cea2d9db-885c-4375-bf08-9ca1b41988c6.png" alt="Set graph window" width=200 />

When the graph is plotted, the program will allow to `zoom-in` or `zoom-out` using the `mouse wheel`. The program will allow to modify the iteration count of the 
fractal using the `arrow-up` and the `arrow-down` (using the arrows, the max count possible is 5 due to the slowness of the graphics library when it has so many line).

## How it works
The program divide into three parts the segment given by the user and place an equilateral triagle insted  of the central segment. Than the operation 
is repeated for all the segments created for the number of time entered by the user.

To represent the snowflake the program creates an equilateral triangle before all the calculations.

## Known issues
When the iteration count is too high the zoom will be jerky due to the slowness of the graphics library when it has so many line.
