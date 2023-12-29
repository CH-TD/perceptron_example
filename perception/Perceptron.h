class Perceptron
{
public:
float* inputs;// Inputs vector
// Perceptron constructor
Perceptron(int ninputs) // int ninputs - number of inputs
{
alpha = 0.001;// Default learning rate
n = ninputs + 1;// Set the number of inputs
inputs = new float[n];// Asking for memory
weights = new float[n];// Bias
inputs[n - 1] = 1;
randomize();// Start with random weights
}
void randomize()// Random weights
{
for (int i = 0; i < n; i++)
{
weights[i] = (float) random(-1000, 1000) / 1000.0;
}
}
void train(int T, float predicted)// Training function
{
float error = T - predicted;
for (int i = 0; i < n; i++)
{
weights[i] += alpha*error*inputs[i];// Update weights
}
}
int feed_forward()// Forward function
{
float sum = 0.0;
for (int i = 0; i < n; i++)
{
sum += inputs[i]*weights[i];
}
return activate(sum);
}
private:
float* weights;// Random weights vector
int n;// Inputs number
float alpha;// Learning rate
int activate(float sum) // Activation function
{
return (sum >= 0) ? 1:-1;// Signum function
}
};
