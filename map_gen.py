import random
import sys, os

current_dir = os.path.dirname(os.path.abspath(__file__))
os.chdir(current_dir)

class ARGS:
	def __init__(self,sys_args):
		self.index = 1
		self.args = sys_args

args = ARGS(sys.argv)

def input_args(args, question, default, values, print_values=True):
	vals = ""
	if print_values:
		vals ="\n".join(values)+"\n"
	if len(args.args) > args.index:
		res = args.args[args.index]
	else:
		res = input(question+"\n"+ vals + "(default: " + default + "): ") or default
	args.index += 1
	if res not in values:
		print("Invalid value")
		sys.exit(1)
	return res

wall_texture = input_args(args, "Wall texture:","neon", ["debug", "neon"])
width = int(input_args(args, "Width","20", [str(i) for i in range(1, 100)],False))
height = int(input_args(args, "Height","20", [str(i) for i in range(1, 100)],False))
ceil = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
floor = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
player_pos = (random.randint(1, width-2), random.randint(1, height-2))
player_dir = ["N", "E", "S", "W"][random.randint(0, 3)]
_map = []
for i in range(height):
	_map.append([0]*width)
for i in range(height):
	for j in range(width):
		if i == 0 or j == 0 or i == height-1 or j == width-1:
			_map[i][j] = 1
		else:
			_map[i][j] = 1 if random.randint(0, 100)<=25 else 0
_map[player_pos[1]][player_pos[0]] = player_dir
#doors
for i in range(1, height-1):
	for j in range(1, width-1):
		if _map[i][j] == 0:
			OK = False
			if _map[i][j-1] == 1 and _map[i][j+1] == 1 and _map[i-1][j] == 0 and _map[i+1][j] == 0:
				OK = True
			elif _map[i][j-1] == 0 and _map[i][j+1] == 0 and _map[i-1][j] == 1 and _map[i+1][j] == 1:
				OK = True
			if OK and random.randint(0, 100)<=25:
				_map[i][j] = 2
txt = ""
if wall_texture == "debug":
	txt += \
"""NO ./assets/tests/missing_n.xpm
SO ./assets/tests/missing_s.xpm
WE ./assets/tests/missing_w.xpm
EA ./assets/tests/missing_e.xpm
"""
else:
	txt += \
"""NO ./assets/world/wall.xpm
SO ./assets/world/wall.xpm
WE ./assets/world/wall.xpm
EA ./assets/world/wall.xpm
"""

txt += "F " + str(floor[0]) + "," + str(floor[1]) + "," + str(floor[2]) + "\n"
txt += "C " + str(ceil[0]) + "," + str(ceil[1]) + "," + str(ceil[2]) + "\n"

for i in range(height):
	for j in range(width):
		txt += str(_map[i][j])
	txt += "\n"

with open("maps/gen_map.cub", "w") as f:
	f.write(txt)
