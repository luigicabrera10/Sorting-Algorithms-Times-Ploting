import matplotlib.pyplot as plt

def get_data():
    f = open ('C:\\Users\\Usuario\\Desktop\\UCSP\\Semestre V\\Análisis y Diseño de Algoritmos\\Semana 4\\times.txt','r')
    txt = f.read()
    f.close()

    decode = txt.split(" \n")[:-1]
    X = [int(num) for num in decode[0].split(" ")]
    Y_ = [times.split(" ") for times in decode[1:]]
    Y = []
    for i in range(len(Y_[0])):
        Y.append([])
        for j in range(len(Y_)):
            Y[i].append(int(Y_[j][i]))
    #print(Y)
    return X, Y

def plot():
    X, Y = get_data()
    config = [("Shell Sort", "r"),("Heap Sort", "m"),("Bucket Sort", "y"),("Merge Sort", "b"),("Quick Sort", "c"),("Radix Sort", "g"),]
    for i in range(len(Y)): plt.plot(X, Y[i], label=config[i][0], color=config[i][1])
    plt.legend()
    plt.show()

plot()