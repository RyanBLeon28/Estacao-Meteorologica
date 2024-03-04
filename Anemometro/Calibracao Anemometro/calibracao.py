import numpy as np
import matplotlib.pyplot as plt 
from sklearn.datasets import make_regression
from sklearn.linear_model import LinearRegression
from scipy.optimize import curve_fit

def coletarAmostras(quant):
    rpm = []
    m_s = []
    resistencia = []
    for i in range(quant):
        varRPM_media = 0
        print("Amostra ",i+1,":" ,end=" ")
        res = float(input("-> Digite a resistencia: "))
        varM_S = float(input("-> Digite m/s: "))
        for k in range(5):
            varRPM = float(input("                Digite RPM: "))
            varRPM_media = varRPM_media + varRPM
        print("\n")
        resistencia.append(res)
        rpm.append(varRPM_media/5)
        m_s.append(varM_S)
    print("\n")
    print("rpm = ",rpm)
    print("m_s =",m_s)
    print("Resistencia =",resistencia)
    return rpm, m_s, resistencia


def selectionSort(lista1, lista2, lista3): 
    for i in range(len(lista1)):
        smallest = i
        for j in range(i+1,len(lista1)):
            if lista1[j] < lista1[smallest]:
                smallest = j

        temp = lista1[i]
        lista1[i] = lista1[smallest]
        lista1[smallest] = temp

        temp2 = lista2[i]
        lista2[i] = lista2[smallest]
        lista2[smallest] = temp2

        temp3 = lista3[i]
        lista3[i] = lista3[smallest]
        lista3[smallest] = temp3

    #print("rpm = ",lista1)
    #print("m/s = ",lista2)
    #print("resistencia = ",lista3)
    return lista1,lista2,lista3

def comparacao(lista1, lista2): 
    for i in range(len(lista1)):
        print("rpm = ",lista1[i],end=" ")
        print("   m/s = ",lista2[i])
    return lista1,lista2

def freq_angular(lista_hz):
    w = []
    for i in range(len(lista_hz)):
        w.append(2 * 3.14 * (lista_hz[i]/60))
    return w


rpm = [981.54, 990.9399999999999, 983.32, 1003.22, 1003.46, 1007.1600000000001, 1013.9400000000002, 1014.3, 1001.24, 995.0600000000001,
        952.0200000000001, 921.1200000000001, 917.72, 935.1, 935.36, 929.3, 919.4200000000001, 939.9800000000001, 948.18, 951.5200000000001,
        788.4, 798.28, 810.0, 821.6, 830.6199999999999, 840.26, 846.0600000000001, 853.8799999999999, 862.1600000000001, 874.4,
        791.26, 789.8399999999999, 808.6800000000001, 810.2800000000001, 835.3799999999999, 837.9199999999998, 851.36, 847.8399999999999, 874.82, 873.7,
        260.7, 255.34, 254.95999999999998, 254.28000000000003, 251.82, 251.88000000000002, 249.68, 248.14000000000001, 248.76, 244.61999999999998,
        432.1, 433.62, 434.1, 435.08000000000004, 436.64, 437.71999999999997, 440.73999999999995, 436.28000000000003, 440.23999999999995, 437.52,
        344.42, 342.8, 343.98, 341.18, 342.0, 343.97999999999996, 338.25999999999993, 337.49999999999994, 334.0, 336.65999999999997,
        500.76000000000005, 496.78000000000003, 500.84000000000003, 501.12, 501.6, 504.08000000000004, 502.78000000000003, 506.0, 506.08000000000004, 507.41999999999996,
        569.62, 571.26, 576.4999999999999, 572.8199999999999, 573.4799999999999, 574.86, 573.8399999999999, 571.52, 573.54, 575.9,
        692.86, 696.5600000000001, 689.28, 692.3199999999999, 692.6200000000001, 694.6800000000001, 695.04, 694.58, 694.7599999999999, 692.66,
        728.32, 724.5200000000001, 728.4, 730.1600000000001, 726.7800000000001, 727.7, 727.36, 727.4000000000001, 728.2, 726.3399999999999,
        1059.9199999999998, 1035.78, 1042.3799999999999, 1029.36, 1025.7800000000002, 1033.16, 1030.1599999999999, 1027.4599999999998, 1026.1, 1025.08,
        746.84, 713.3199999999999, 729.74, 738.64, 750.3, 760.7, 768.8199999999999, 798.8199999999999, 798.1600000000001, 789.8,
        616.96, 615.8800000000001, 618.5600000000001, 616.84, 616.76, 617.1800000000001, 615.16, 614.88, 615.7, 612.36,
        780.36, 774.4200000000001, 779.1600000000001, 779.3799999999999, 779.6600000000001, 778.8799999999999, 777.9399999999999, 777.98, 777.2199999999999, 779.86]

m_s = [17.8, 17.9, 18.0, 18.1, 18.3, 18.3, 18.4, 18.5, 18.3, 18.2, 
       17.2, 16.7, 16.6, 17.0, 17.1, 16.8, 16.7, 17.0, 17.1, 17.3,
       14.3, 14.5, 14.6, 14.9, 15.2, 15.0, 15.3, 15.5, 15.7, 15.9,
        14.4, 14.4, 14.6, 14.8, 15.3, 15.2, 15.5, 15.5, 15.9, 15.8,
        5.0, 4.8, 4.8, 4.8, 4.8, 4.8, 4.7, 4.8, 4.6, 4.5,
        8.0, 7.9, 8.0, 8.0, 8.0, 8.0, 8.0, 8.1, 8.1, 8.1,
        6.4, 6.4, 6.4, 6.4, 6.4, 6.4, 6.3, 6.3, 6.3, 6.2,
        9.3, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.2, 9.3, 9.3,
        10.4, 10.4, 10.4, 10.4, 10.5, 10.5, 10.4, 10.5, 10.5, 10.4,
        12.6, 12.5, 12.6, 12.6, 12.5, 12.6, 12.6, 12.5, 12.6, 12.6,
        13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.2, 13.1, 13.2,
        19.4, 18.8, 18.8, 18.6, 18.7, 18.8, 18.9, 18.6, 18.7, 18.5,
        12.7, 13.0, 13.2, 13.4, 13.6, 13.8, 14.0, 14.5, 14.4, 14.5,
        11.1, 11.2, 11.2, 11.2, 11.2, 11.3, 11.3, 11.2, 11.1, 11.2,
        14.0, 14.2, 14.1, 14.2, 14.1, 14.1, 14.2, 14.2, 14.0, 14.1]

resistencia = [8.0, 8.1, 8.2, 8.3, 8.4, 8.5, 8.7, 8.8, 8.9, 9.0,
        7, 7, 7, 7.3, 7.3, 7.3, 7.6, 7.6, 7.8, 8,        
        5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 6.0,
        5.0, 5.0, 5.2, 5.2, 5.5, 5.5, 5.7, 5.7, 6.0, 6.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
        1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5,
        2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5,
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
        4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0,
        4.5, 4.5, 4.5, 4.5, 4.5, 4.5, 4.5, 4.5, 4.5, 4.5,
        9.0, 9.1, 9.2, 9.3, 9.4, 9.5, 9.7, 9.8, 9.9, 10.0,
        4.0, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 5.0, 5.0, 5.0,
        3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5, 3.5,
        5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0]


# ------------- Coletar amostras ----------------------------------
#rpm, m_s, resistencia = coletarAmostras(10)

# ------------- Lista de frequencia angular ------------------------
w = []
w = freq_angular(rpm)

# ------------- Ordena a lista de frequencia angular e  m/s com o seu respectivo ------------- 
w, m_s, resistencia = selectionSort(w,m_s,resistencia)

# ------------- Função para comparar os valores da amostra ----------
#comparacao(w, m_s)


#------------- Dados a partir de freq ang e vel ---------------------
print("Tamanho da amostra: ",len(w))
print("w minimo:",np.min(w),"   m/s minimo: ",np.min(m_s))
print("w maximo:",np.max(w),"   m/s máximo: ",np.max(m_s),"\n")
print("Media de freq. angular:       ",np.average(w))
print("Desvio padrao de freq. angular:",np.std(w),"\n")


#------------- Regressão linear (freq ang, velocidade---------------------------------------
 
#w,m_s = make_regression(n_samples=len(w), n_features=1, noise=30)

w= np.array(w)
w = w.reshape(-1,1)

modelo = LinearRegression()
modelo.fit(w,m_s)

a_coeff = modelo.coef_
l_coeff = modelo.intercept_
print("Equação da reta da regressão linear")
print("{0}x + {1}".format(a_coeff,l_coeff))

plt.scatter(w,m_s)
#plt.plot(w, a_coeff[0]*w + l_coeff, color="red")

plt.plot(w, a_coeff[0]*w + l_coeff, color="red")
plt.xlabel('Freq ang')
plt.ylabel('Velocidade')



#------------- Regressão linear (resistencia,freq angular) ---------------------------------------
 
#w,m_s = make_regression(n_samples=len(w), n_features=1, noise=30)

resistencia= np.array(resistencia)
resistencia = resistencia.reshape(-1,1)


modelo = LinearRegression()
modelo.fit(np.log(resistencia),w)

a_coeff = modelo.coef_
l_coeff = modelo.intercept_
print("Equação da reta da regressão linear")
print("{0}x + {1}".format(a_coeff,l_coeff))

plt.figure()
plt.scatter(resistencia,w)
plt.plot(resistencia, (np.log(resistencia))*a_coeff + l_coeff, color="red")
plt.xlabel('resistencia')
plt.ylabel('Freq ang')


#plt.show()

