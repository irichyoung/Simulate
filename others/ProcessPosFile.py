import re,os
def process(filepath):
	with open(filepath) as f:
		s = re.findall(r'-?\d+\.?\d*e?-?\d*?',f.read())
		with open("Processed" + filepath,"w") as wf:
			count = 0
			for each in s:
				if count % 12 == 0:
					wf.write("\n")
				wf.write(each + " ")
				count += 1

def traversalTxt(path):
	filepath = os.listdir(path)
	for p in filepath:
		if os.path.splitext(p)[1] == ".txt":
			process(p)


traversalTxt(os.path.abspath('.'))