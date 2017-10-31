import matplotlib.pyplot as plt
import scipy.stats as stats

lower1, upper1 = 1, 65
mu1, sigma1 = 5, 20

lower2, upper2 = 1, 70
mu2, sigma2 = 10, 20

#X = stats.truncnorm((lower - mu) / sigma, (upper - mu) / sigma, loc=mu, scale=sigma)

#file_object = open('test_World.txt', "r")

file_object = open('world.txt', "r")
while 1:
    lines = file_object.readlines(100)
    if not lines:
        break;
    for line in lines:
        parts = line.split(' ')
        if parts[0] == 'L':
            fromL, toL = parts[2], parts[3]
            file_name = 'file/' + str(fromL) + '_' + str(toL) + '.txt'
            wfile = open(file_name, 'a+')
            count = 0
            lower, upper = 1, 65
            mu, sigma = 5, 20
            datas = []
            if  float(parts[4]) > 20:
                mu, sigma = 10, 20
                lower, upper = 1, 70
            N = stats.norm(loc = mu, scale=sigma)
            temp = N.rvs(100000)
            for data in temp:
                if data >= lower and data <= upper:
                    datas.append(int(data) * 128)
            for data in datas:
                info = str(count) + ' ' + str(data) + '\n'
                wfile.write(info)
                count = count + 1

#keytomap = {}
#for data in datas1:
    #if not keytomap.has_key(data):
        #keytomap[data] = 1
    #else:
        #keytomap[data] = keytomap[data] + 1;

#E = 0
#for key, value in keytomap.items():
    #E = E + key * (float(value) / float(len(datas1)))

#print E

#print keytomap

#fig, ax = plt.subplots(2, sharex=True)
#ax[0].hist(X.rvs(10000), normed=True)
#ax[1].hist(N.rvs(10000), normed=True)
#plt.show()
