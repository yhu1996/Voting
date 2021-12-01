import matplotlib.pyplot as plt
import numpy as np


def Red(fname):
    TriangleRed,Nred = np.loadtxt(fname,delimiter=",",unpack=True)
    plt.figure()
    plt.plot(TriangleRed,Nred,marker="o",markersize=3,linestyle="None")
    plt.xlabel("TriangleRed")
    plt.ylabel("Nred")
    plt.savefig(fname[:-3]+".png",dpi=300)
    plt.close()

def main():
    print("this is main")
    Red("TriangleRed0~N_red(p=0.3,T=0.03,step=10000),1000simul.dat")

if __name__ == '__main__':
    main()