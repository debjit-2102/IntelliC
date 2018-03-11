#include "csv_handler.cpp"
#include "data_analyzer.cpp"
#include "data_transform.cpp"
#include "neural_network.cpp"
#include "vector.cpp"
#include "matrix.cpp"
using namespace std;
int main(){
	CSVHandler c("train_handwriting.csv");
	vector <vector <double> > data;
	vector <string> label;
	c.readCSV(data, label);
	vector <vector <double> > X_train;
	vector <vector <double> > Y_train;
	for(int i=0;i<data.size();i++){
		X_train.push_back(data[i]);
		vector <double> row (10, 0);
		row[(int)data[i][0]] = 1;
		Y_train.push_back(row);
	}
	DataTransform <double> dt;
	X_train = dt.sliceColumn(X_train,1,785);

	vector <int> v;
	v.push_back(25);
	NeuralNetwork model(X_train, Y_train, v, 100);
	model.trainByGradientDescent(0.01, true);
	vector <vector <double> > Y_p = model.predict(X_train);
	for(int i=0;i<Y_p.size();i++){
		for(int j=0;j<Y_p[i].size();j++){
			printf("%lf ",Y_p[i][j]);
		}
		printf("\n");
	}
	return 0;
}