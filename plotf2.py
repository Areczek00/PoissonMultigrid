import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure


k = 16
while k >= 1:
    file = f'potencjalk_{k}.txt'	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data
    #print(data)
    #data.transpose()
    X1 = data[:,0]
    Y1 = data[:,1]
    V1 = data[:,2]

    #plt.imshow(data, vmin=data.min(), vmax=data.max(), cmap='seismic', origin='lower')
    v = V1.reshape((128//k , 128//k ))
    x = X1.reshape((128//k , 128//k ))
    y = Y1.reshape((128//k ,128//k ))

    plt.pcolor(x, y, v, cmap='seismic')
    plt.colorbar(label = 'Potencjal')

    plt.xlabel('x')	# tytuly osi i wykresu
    plt.ylabel('y')
    plt.title(f'k = {k}')

    #plt.grid()	# siatka pomocnicza
    plt.savefig(f'potencjal_k_{k}')	# zapis wykresu do pliku
    fig = plt.figure()
    k = k//2

file = "S(it)k_16.txt"	# wczytanie pliku z danymi
data = np.loadtxt(file)	# do tablicy data

file2 = "S(it)k_8.txt"
data2 = np.loadtxt(file2)

file3 = "S(it)k_4.txt"
data3 = np.loadtxt(file3)

file4 = "S(it)k_2.txt"
data4 = np.loadtxt(file4)

file5 = "S(it)k_1.txt"
data5 = np.loadtxt(file5)

it = data[:, 0]	
S = data[:, 1]
a = 0
for row in it:
    a += 1
plt.plot(it, S, '-', lw=2, label=f'k = 16, it = 1-{a}') # rysowanie wykresu

it = data2[:, 0]	
S = data2[:, 1]
g = a
for row in it:
    a += 1
plt.plot(it, S, '-', lw=2, label=f'k=8, it = {g}-{a}') # rysowanie wykresu

it = data3[:, 0]	
S = data3[:, 1]
g = a
for row in it:
    a += 1
plt.plot(it, S, '-', lw=2, label=f'k=4, it = {g}-{a}') # rysowanie wykresu

it = data4[:, 0]	
S = data4[:, 1]
g = a
for row in it:
    a += 1
plt.plot(it, S, '-', lw=2, label=f'k = 2, it = {g}-{a}') # rysowanie wykresu

it = data5[:, 0]	
S = data5[:, 1]
g=a
for row in it:
    a += 1
plt.plot(it, S, '-', lw=2, label=f'k = 1, it = {g}-{a}') # rysowanie wykresu

plt.xlabel('it')	# tytuly osi i wykresu
plt.ylabel('S(it)')
plt.title('S(it, k)')
l1 = plt.legend()	# legenda
plt.grid()	# siatka pomocnicza
plt.savefig("S(it).png")	# zapis wykresu do pliku