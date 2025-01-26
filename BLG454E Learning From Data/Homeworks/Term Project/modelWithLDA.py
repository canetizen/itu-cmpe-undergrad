# Mustafa Can Caliskan, 150200097
# Yusuf Sahin, 150200016


# Implementation of LDA

import numpy as np

class LDA:
    def __init__(self, n_components=50):
        self.n_components = n_components
        self.projection_matrix = None

    def fit(self, X, y):
        n_features = X.shape[1]
        class_labels = np.unique(y)
        n_classes = len(class_labels)

        class_means = np.zeros((n_classes, n_features))
        for label in class_labels:
            class_means[class_labels == label, :] = np.mean(X[y == label], axis=0)

        within_class_scatter = np.zeros((n_features, n_features))
        for label in class_labels:
            class_scatter = np.zeros((n_features, n_features))
            for row in X[y == label]:
                row, mean_vec = row.reshape(n_features, 1), class_means[class_labels == label].reshape(n_features, 1)
                class_scatter += (row - mean_vec).dot((row - mean_vec).T)
            within_class_scatter += class_scatter

        overall_mean = np.mean(X, axis=0)
        between_class_scatter = np.zeros((n_features, n_features))
        for label in class_labels:
            n_samples_per_class = len(X[y == label])
            mean_vec = class_means[class_labels == label].reshape(n_features, 1)
            between_class_scatter += n_samples_per_class * (mean_vec - overall_mean).dot((mean_vec - overall_mean).T)

        # Add a small regularization term to within_class_scatter
        within_class_scatter += 1e-4 * np.eye(n_features)

        try:
            # Use a more stable method to solve the eigenvalue problem
            eigenvalues, eigenvectors = np.linalg.eigh(np.linalg.inv(within_class_scatter).dot(between_class_scatter))
        except np.linalg.LinAlgError:
            # Handle singular matrix by adding a small diagonal perturbation
            perturbation = 1e-4 * np.eye(n_features)
            eigenvalues, eigenvectors = np.linalg.eigh(np.linalg.inv(within_class_scatter + perturbation).dot(between_class_scatter))

        eigen_pairs = [(np.abs(eigenvalues[i]), eigenvectors[:, i]) for i in range(len(eigenvalues))]
        eigen_pairs = sorted(eigen_pairs, key=lambda k: k[0], reverse=True)

        self.projection_matrix = np.hstack((eigen_pairs[0][1].reshape(n_features, 1), eigen_pairs[1][1].reshape(n_features, 1)))

        # Transform the data and return the transformed data
        X_transformed = X.dot(self.projection_matrix)
        return X_transformed
        
    def transform(self, X):
        return X.dot(self.projection_matrix)



########## MACHINE LEARNING MODEL ##################
import pandas as pd
import numpy as np
from sklearn.impute import SimpleImputer
from sklearn.ensemble import RandomForestClassifier

# Read the dataset
df = pd.read_csv("aps_failure_training_set.csv", na_values="na")
df_test = pd.read_csv("aps_failure_test_set.csv", na_values="na")

# Configurate the data columns
X = df.drop(['id', 'class'], axis=1)
y = df['class']
X_last = df_test.drop(['id'], axis=1)

threshold = 0.67
missing_portion = df.isnull().mean()
cols_to_drop = missing_portion[missing_portion > threshold].index
X = X.drop(cols_to_drop, axis=1)
X_last = X_last.drop(cols_to_drop, axis=1)

# Handle missing values using IterativeImputer
imputer = SimpleImputer(strategy='median')
X_imputed = imputer.fit_transform(X)
X_last_imputed = imputer.transform(X_last)

# Apply LDA
lda = LDA(n_components=75)
X_transformed = lda.fit(X_imputed, y)
X_last_transformed = lda.transform(X_last_imputed)

# Rest of our modal
rfc = RandomForestClassifier(n_estimators=100, random_state=60)
rfc.fit(X_transformed, y)
y_pred = rfc.predict(X_last_transformed)

ids = df_test['id'].tolist()
df_result = pd.DataFrame({
    'id' : ids,
    'class' : y_pred
})

df_result.to_csv('predictionsLDA.csv', index=False)
