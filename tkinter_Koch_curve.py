from dataclasses import dataclass
from subprocess import check_output
from PIL import Image, ImageTk
import tkinter as tk


WIDTH = 500
HEIGHT = 500


@dataclass
class Coords2D:
    x: float
    y: float


class Graph:
    root: tk
    graph: tk.Canvas

    start: Coords2D
    goal: Coords2D
    count: int

    option: str

    points = []

    def __init__(self, root, start, goal, count, option):
        self.root = root

        self.start = start
        self.goal = goal
        self.count = count

        self.option = option

        self.set_points()

    def set_points(self):
        self.points = eval(check_output(
            [str(self.option),
             str(self.start.x), str(self.start.y),
             str(self.goal.x), str(self.goal.y),
             str(self.count)],
            shell=True).decode('utf-8')
        )

    def inc_count(self, event):
        self.count += 1 if event.keysym == "Up" and self.count < 5 else\
                     -1 if event.keysym == "Down" and self.count > 0\
                     else 0
        self.clear()
        self.set_points()
        self.draw()

    def zoom(self, event):
        scale = 1.1 if event.delta > 0 else 0.9
        self.graph.scale('all', event.x, event.y, scale, scale)

    def draw(self):
        self.graph = tk.Canvas(self.root, width=WIDTH, height=HEIGHT)
        for i in range(len(self.points) - 1):
            self.graph.create_line(self.points[i].x, self.points[i].y, self.points[i + 1].x, self.points[i + 1].y)
        self.graph.pack()

    def clear(self):
        self.graph.destroy()


def init_window(root):
    root.title("Curva di Koch")
    root.withdraw()
    root.wm_iconphoto(False, ImageTk.PhotoImage(Image.open('icon.ico')))
    root.minsize(240, 200)
    root.resizable(False, False)


def get_values_frame(root):
    frame = tk.Frame(root)
    frame.pack()

    start_x = tk.Label(frame, text=f"Start x: ")
    start_x.grid(row=0, column=0, padx=5, pady=5, sticky=tk.E)
    start_y = tk.Label(frame, text=f"Start y: ")
    start_y.grid(row=1, column=0, padx=5, pady=5, sticky=tk.E)
    goal_x = tk.Label(frame, text=f"Goal x: ")
    goal_x.grid(row=2, column=0, padx=5, pady=5, sticky=tk.E)
    goal_y = tk.Label(frame, text=f"Goal y: ")
    goal_y.grid(row=3, column=0, padx=5, pady=5, sticky=tk.E)
    count_label = tk.Label(frame, text=f"Count: ")
    count_label.grid(row=4, column=0, padx=5, pady=5, sticky=tk.E)

    entries = []
    for i in range(5):
        entry = tk.Entry(frame)
        entry.grid(row=i, column=1, padx=5, pady=5, sticky=tk.W)
        entries.append(entry)

    entries[0].insert(0, "50")
    entries[1].insert(0, "350")
    entries[2].insert(0, "450")
    entries[3].insert(0, "350")
    entries[4].insert(0, "5")

    selected_option = tk.StringVar()
    options_list = ["Koch Curve", "Koch Snowflake"]
    strings_list = ["bin\\Koch_curve.exe", "bin\\Koch_snowflake.exe"]
    option_value_dict = {option: value for option, value in zip(options_list, strings_list)}
    selected_option.set(options_list[0])

    frame_submit = tk.Frame(root)
    frame_submit.pack()

    dropdown = tk.OptionMenu(frame_submit, selected_option, *options_list)
    dropdown.grid(row=0, column=0, padx=5, pady=5, sticky=tk.W)

    button = tk.Button(frame_submit, text="Submit", command=lambda: create_graph())
    button.grid(row=0, column=1, padx=5, pady=5, sticky=tk.E)

    def create_graph():
        def get_user_input():
            values = []
            for entry in entries:
                try:
                    value = int(entry.get())
                    values.append(value)
                except ValueError:
                    entry.delete(0, tk.END)
                    return False

            return values

        if not get_user_input():
            return

        root.withdraw()

        user_input = get_user_input()

        frame.destroy()
        frame_submit.destroy()

        start = Coords2D(user_input[0], user_input[1])
        goal = Coords2D(user_input[2], user_input[3])
        count = user_input[4] - 1

        graph = Graph(root, start, goal, count, option_value_dict[selected_option.get()])
        graph.draw()

        root.bind("<MouseWheel>", graph.zoom)
        root.bind("<Key>", graph.inc_count)

        root.deiconify()

    root.deiconify()


def main():
    root = tk.Tk()

    init_window(root)

    get_values_frame(root)

    root.mainloop()


if __name__ == "__main__":
    main()
