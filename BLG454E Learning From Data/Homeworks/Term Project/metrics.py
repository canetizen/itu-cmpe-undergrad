# Mustafa Can Caliskan, 150200097
# Yusuf Sahin, 150200016


from imblearn.under_sampling import RandomUnderSampler
from sklearn.ensemble import RandomForestClassifier
from sklearn.impute import SimpleImputer
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report


df = pd.read_csv("aps_failure_training_set.csv", na_values="na")

X = df.drop(['id', 'class'], axis=1)
y = df['class']


threshold = 0.67
missing_portion = df.isnull().mean()
cols_to_drop = missing_portion[missing_portion > threshold].index
X = X.drop(cols_to_drop, axis=1)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=60)

# Apply Min-Max Normalization to scale the data 
from modelWithLDA import LDA

imputer = SimpleImputer(strategy='median')
X_res = imputer.fit_transform(X_train)
X_last = imputer.fit_transform(X_test)

#Apply LDA
lda = LDA(n_components=75)
X_reduced = lda.fit(X_res, y_train)
X_last_reduced = lda.transform(X_last)

rfc = RandomForestClassifier(n_estimators=100, random_state=60)
rfc.fit(X_reduced, y_train)

# Make predictions on the test set
y_pred = rfc.predict(X_last_reduced)

# Calculate the metrics
print("Classification Report:")
print(classification_report(y_test, y_pred))
