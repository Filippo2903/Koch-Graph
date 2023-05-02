import turtle
from subprocess import check_output
from tkinter import Image
from dataclasses import dataclass


@dataclass
class Coords2D:
    x: float
    y: float


WIDTH = 1000
HEIGHT = 500


def koch_curve_points(start, goal, n):
    return eval(check_output([str('Koch_curve.exe'), str(start.x), str(start.y), str(goal.x), str(goal.y), str(n)],
                             shell=False).decode('utf-8'))


def init_turtle(start):
    turtle.title("Curva di Koch")
    turtle._Screen._root.iconphoto(True, Image("photo", file="./icon.png"))
    turtle.setup(WIDTH, HEIGHT)
    turtle.setworldcoordinates(0, -HEIGHT / 3 * 2, WIDTH + WIDTH / 100, HEIGHT / 3)
    turtle.hideturtle()
    turtle.speed(10)
    turtle.penup()
    turtle.goto(start.x, start.y)
    turtle.pendown()


def main():
    start = Coords2D(0, 0)
    goal = Coords2D(WIDTH, 0)

    init_turtle(start)

    for point in koch_curve_points(start, goal, 4):
        turtle.goto(point.x, point.y)

    turtle.exitonclick()


if __name__ == '__main__':
    main()
