import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Homework2 {

    private static final double[][] P = {{1. / 3, 1. / 2, 1. / 6}, {0, 1. / 4, 3. / 4}, {1. / 2, 1. / 4, 1. / 4}};
    private static final int N = P.length;

    public static void main(String[] args) {
        double[] probabilities = getProbability();
        double entropy = getEntropy(probabilities);
        double conditionalEntropy = getConditionalEntropy(probabilities);
        double[] tmp = new double[2];
        getBlockEntropy(tmp, probabilities);

        for (int i = 0; i < N; i++) {
            System.out.println("p_" + (char) ('a' + i) + " = " + getDouble(probabilities[i]));
        }
        System.out.println("H(X) = " + getDouble(entropy));
        System.out.println("H(X|X^inf) = " + getDouble(conditionalEntropy));
        System.out.println("H_2(X) = " + getDouble((tmp[0] + tmp[1] / 2)));
        System.out.println("H_n(X) = " + getDouble(tmp[0]) + " + " + getDouble(tmp[1]) + " / n");
        Map<String, String> code = getHuffmanCode(1, probabilities);
        System.out.println("Код Хаффмена данного источника для слов длины 1:");
        for (String symbol : code.keySet()) {
            System.out.println(symbol + " " + code.get(symbol));
        }
        code = getHuffmanCode(2, probabilities);
        System.out.println("Код Хаффмена данного источника для слов длины 2:");
        for (String symbol : code.keySet()) {
            System.out.println(symbol + " " + code.get(symbol));
        }
    }

    private static String getDouble(double value) {
        return String.format("%.4f", value);
    }

    // вычисляет вероятность символов, решая
    // систему уравнений (методом Крамера)
    public static double[] getProbability() {
        double[] probabilities = new double[N];
        double[][] equations = new double[N][N];
        double[] free = new double[N];
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N; j++) {
                equations[i][j] = P[j][i];
            }
            equations[i][i] -= 1;
            free[i] = 0;
        }
        for (int i = 0; i < N; i++) {
            equations[N - 1][i] = 1;
        }
        free[N - 1] = 1;
        double delta = determinant(equations);
        for (int k = 0; k < N; k++) {
            double[][] kMatrix = new double[N][N];
            for (int i = 0; i < N; i++) {
                System.arraycopy(equations[i], 0, kMatrix[i], 0, N);
            }
            for (int i = 0; i < N; i++) {
                kMatrix[i][k] = free[i];
            }
            probabilities[k] = determinant(kMatrix);
        }
        for (int i = 0; i < N; i++) {
            probabilities[i] /= delta;
        }
        return probabilities;
    }

    // вычисляет детерминант матрицы 3x3
    private static double determinant(double[][] m) {
        return (m[0][0] * m[1][1] * m[2][2] + m[1][0] * m[2][1] * m[0][2] + m[2][0] * m[0][1] * m[1][2])
                - (m[2][0] * m[1][1] * m[0][2] + m[1][0] * m[0][1] * m[2][2] + m[0][0] * m[2][1] * m[1][2]);
    }

    // вычисляет энтропию источника
    public static double getEntropy(double[] probabilities) {
        double entropy = 0.;
        for (double probability : probabilities) {
            if (probability == 0.) {
                continue;
            }
            entropy += probability * log2(probability);
        }
        return -entropy;
    }

    // вычисляет условную энтропию для источника
    public static double getConditionalEntropy(double[] probabilities) {
        double entropy = 0.;
        for (int i = 0; i < N; i++) {
            entropy += probabilities[i] * getEntropy(P[i]);
        }
        return entropy;
    }

    // вычисляет энтропию на блок
    public static void getBlockEntropy(double[] result, double[] probabilities) {
        result[0] = getConditionalEntropy(probabilities);
        result[1] = getEntropy(probabilities) - getConditionalEntropy(probabilities);
    }

    // вычисляет двоичный логарифм числа
    private static double log2(double value) {
        return Math.log(value) / Math.log(2);
    }

    // вычисляет коды Хаффмена для данного источника, для блоков длины n
    public static Map<String, String> getHuffmanCode(int n, double[] probabilities) {
        Map<String, Double> symbolsFrequency = new HashMap<>();
        int size = (int) Math.pow(probabilities.length, n);
        String[] sequences = new String[size];
        double[] seqProb = new double[size];
        Arrays.fill(sequences, "");
        Arrays.fill(seqProb, 1);

        for (int i = 0; i < n; i++) {
            int count = (int) Math.pow(N, i);
            for (int j = 0; j < size; j++) {
                int letter = (j / count) % N;
                sequences[j] += (char) ('a' + letter);
                try {
                    seqProb[j] *= P[sequences[j].charAt(sequences[j].length() - 2)
                            - 'a'][letter];
                } catch (IndexOutOfBoundsException e) {
               `     seqProb[j] *= probabilities[letter];
                }
            }
        }

        for (int i = 0; i < size; i++) {
            if (seqProb[i] != 0) {
                symbolsFrequency.put(sequences[i], seqProb[i]);
            }
        }

        double expectedValue = 0.;
        Map<String, String> huffmanCodes = generateHuffmanCode(symbolsFrequency);
        for (String block : huffmanCodes.keySet()) {
            expectedValue += (huffmanCodes.get(block).length()
                    * symbolsFrequency.get(block));
        }
        System.out.println("Среднее количество бит на символ при n = " + n
                + " равно " + getDouble(expectedValue / n));
        return huffmanCodes;
    }

    // вычисляет кодовые слова для заданных последовательностей
    private static Map<String, String> generateHuffmanCode(
            Map<String, Double> symbols) {
        Map<String, Double> symbolsFrequency = new HashMap<>(symbols);
        if (symbolsFrequency.size() == 1) {
            Map<String, String> code = new HashMap<>();
            code.put(symbolsFrequency.keySet().iterator().next(), "");
            return code;
        }
        String symbolMin = null;
        String symbolNextMin = null;
        double frequencyMin = Double.MAX_VALUE;
        double frequencyNextMin = Double.MAX_VALUE;
        for (String symbol : symbolsFrequency.keySet()) {
            double frequency = symbolsFrequency.get(symbol);
            if (frequency < frequencyMin) {
                frequencyNextMin = frequencyMin;
                symbolNextMin = symbolMin;
                frequencyMin = frequency;
                symbolMin = symbol;
            } else if (frequency < frequencyNextMin) {
                frequencyNextMin = frequency;
                symbolNextMin = symbol;
            }
        }
        symbolsFrequency.remove(symbolMin);
        symbolsFrequency.remove(symbolNextMin);
        String newSymbol = symbolMin + symbolNextMin;
        symbolsFrequency.put(newSymbol, frequencyMin + frequencyNextMin);
        Map<String, String> codeMap = generateHuffmanCode(symbolsFrequency);
        String code = codeMap.remove(newSymbol);
        codeMap.put(symbolMin, code + "0");
        codeMap.put(symbolNextMin, code + "1");
        return codeMap;
    }

}
