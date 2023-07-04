from sklearn import datasets
from sklearn import model_selection
from sklearn.neighbors import KNeighborsClassifier

def loadData():
    wine = datasets.load_wine()
    return model_selection.train_test_split(wine.data[:,:2], wine.target, train_size=0.8, random_state=42)

def uniform(X_train, y_train):
    knn = KNeighborsClassifier(n_neighbors=15, weights='uniform')
    knn.fit(X_train, y_train)
    return knn

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return (res == y_test).mean()
