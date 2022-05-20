package main;

import Santa.Santa;
import children.*;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import common.Constants;
import gifts.Gift;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Simulation {
    private Santa santa;
    private ArrayList<ArrayList<Double>> niceScoreList = new ArrayList<ArrayList<Double>>();
    private int simulationRound = 0;
    private Double averageScoreSum = Double.valueOf(0);
    private ArrayList<Child> childrenList = new ArrayList<Child>();
    public int numberOfYears = 0;
    private ArrayList<AnnualChanges> annualChanges = new ArrayList<AnnualChanges>();
    private ArrayList<JSONArray> jsonYearlyChildren = new ArrayList<>();
    private ArrayList<AnnualChildren> annualChildrenList = new ArrayList<>();

    public ArrayList<AnnualChildren> getAnnualChildren() {
        return annualChildrenList;
    }

    public void setAnnualChildren(ArrayList<AnnualChildren> annualChildrenList) {
        this.annualChildrenList = annualChildrenList;
    }

    public Simulation() {
        this.santa = new Santa();
    }

    public ArrayList<JSONArray> getJsonYearlyChildren() {
        return jsonYearlyChildren;
    }

    public void setJsonYearlyChildren(ArrayList<JSONArray> jsonYearlyChildren) {
        this.jsonYearlyChildren = jsonYearlyChildren;
    }

    public Santa getSanta() {
        return santa;
    }

    public void setSanta(Santa santa) {
        this.santa = santa;
    }

    public ArrayList<ArrayList<Double>> getNiceScoreList() {
        return niceScoreList;
    }

    public void setNiceScoreList(ArrayList<ArrayList<Double>> niceScoreList) {
        this.niceScoreList = niceScoreList;
    }

    public Double getAverageScoreSum() {
        return averageScoreSum;
    }

    public void setAverageScoreSum(Double averageScoreSum) {
        this.averageScoreSum = averageScoreSum;
    }

    public ArrayList<Child> getChildrenList() {
        return childrenList;
    }

    public void setChildrenList(ArrayList<Child> childrenList) {
        this.childrenList = childrenList;
    }

    public ArrayList<AnnualChanges> getAnnualChanges() {
        return annualChanges;
    }

    public void setAnnualChanges(ArrayList<AnnualChanges> annualChanges) {
        this.annualChanges = annualChanges;
    }

    public void sortChildrenList() {
        Child auxI, auxJ;
        for (int i = 0; i < this.childrenList.size() - 1; i++) {
            for (int j = i + 1; j < this.childrenList.size(); j++) {
                if (this.childrenList.get(i).getId() > this.childrenList.get(j).getId()) {
                    auxI = new Child(this.childrenList.get(i));
                    auxJ = new Child(this.childrenList.get(j));
                    this.childrenList.remove(i);
                    this.childrenList.add(i, auxJ);
                    this.childrenList.remove(j);
                    this.childrenList.add(j, auxI);
                }
            }
        }
    }

    //aici citim doar datele de intrare pentru primul an
    // si le incarcam in obiecte
    public void readTestInput(final Integer testNumber) {
        JSONParser jsonParser = new JSONParser();

        try {
            String inputFile = Constants.TESTS_PATH + testNumber
                    + Constants.FILE_EXTENSION;
            JSONObject jsonObject = (JSONObject) jsonParser.parse(new FileReader(inputFile));

            this.numberOfYears = (int) (long) jsonObject.get("numberOfYears");
            santa.santaBudget = (double) (int) (long) jsonObject.get("santaBudget");

            JSONObject jsonInitialData = (JSONObject) jsonObject.get("initialData");
            JSONArray jsonChildrenList = (JSONArray) jsonInitialData.get("children");
            for (int i = 0 ; i < jsonChildrenList.size(); i++) {
                JSONArray jsonGiftPreferences =
                        (JSONArray) ((JSONObject) jsonChildrenList.get(i)).get("giftsPreferences");
                Child auxChild = new Child((JSONObject) jsonChildrenList.get(i), jsonGiftPreferences);
                if (auxChild.getAge() <= 18) {
                    this.childrenList.add(auxChild);
                }
            }
            //mai sus am citit vectorul de copii, i-am creat in memorie si i-am adaugat
            // in lista noastra de copii

            //acum o sa sortam lista dupa id-uri (crescator)
            this.sortChildrenList();

            JSONArray jsonSantaGifts = (JSONArray) jsonInitialData.get("santaGiftsList");
            for (int i = 0; i < jsonSantaGifts.size(); i++) {
                Gift auxGift = new Gift((JSONObject) jsonSantaGifts.get(i));
                santa.santaGiftsList.add(auxGift);
            }

            JSONArray jsonAnnualChanges = (JSONArray) jsonObject.get("annualChanges");
            for (int i = 0; i < jsonAnnualChanges.size(); i++) {
                JSONArray jsonNewGifts =
                        (JSONArray) ((JSONObject) jsonAnnualChanges.get(i)).get("newGifts");
                JSONArray jsonNewChildren =
                        (JSONArray) ((JSONObject) jsonAnnualChanges.get(i)).get("newChildren");
                JSONArray jsonChildrenUpdates =
                        (JSONArray) ((JSONObject) jsonAnnualChanges.get(i)).get("childrenUpdates");

                AnnualChanges auxAnnualChanges = new AnnualChanges((JSONObject) jsonAnnualChanges.get(i),
                        jsonNewGifts, jsonNewChildren, jsonChildrenUpdates);
                this.annualChanges.add(auxAnnualChanges);
            }
        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }
    }

    //oferim ca parametru un obiect de tip Child
    //si metoda returneaza obiectul JSON specific acestuia
    //ne ajuta la outputul final din fisier-ul JSON
    public JSONObject getJsonChild(Child child) {
        JSONObject jsonChild = new JSONObject();
        JSONArray jsonReceivedGifts = new JSONArray();

        jsonChild.put("id", child.getId());
        jsonChild.put("lastName", child.getLastName());
        jsonChild.put("firstName", child.getFirstName());
        jsonChild.put("city", capitalize(child.getCity().toString().toLowerCase()));
        jsonChild.put("age", child.getAge());
        jsonChild.put("giftPreferences", transformPreferencesForOutput(child));
        jsonChild.put("averageScore", child.getAverageScore());
        jsonChild.put("niceScoreHistory", child.getNiceScore());
        jsonChild.put("assignedBudget", child.getFirstAssignedBudget());
        for (int i = 0; i < child.getReceivedGifts().size(); i++) {
            jsonReceivedGifts.add(child.getReceivedGifts().get(i).getJSONGift());
        }
        jsonChild.put("receivedGifts", jsonReceivedGifts);
        return jsonChild;
    }

    //in aceasta functie facem operatiile simple, repetitive,
    // dupa ce am updatat datele de intrare
    public void SimulatingYear(Santa santa) {
        AnnualChildren auxAnnualChildren = new AnnualChildren();
        //calculam averageScore pentru fiecare copil
        for (int i = 0; i < childrenList.size(); i++) {
            childrenList.get(i).calculateAverageScore();
        }
        calculateAverageScoreSum();
        //calculam Santa.budgetUnit
        santa.calculateBudgetUnit();
        //pentru fiecare copil
        for (int i = 0 ; i < childrenList.size(); i++) {
            //calculam assignedBudget,
            // ca sa stim ce buget avem pentru cadourile lui
            this.childrenList.get(i).calculateAssignedBudget(santa);
            //apoi ii oferim cadourile
            santa.giveGiftsToChild(this.childrenList.get(i));
        }
//        auxAnnualChildren.setChildren(this.childrenList);
//        this.getAnnualChildren().add(auxAnnualChildren);
        this.getJsonYearlyChildren().add(this.getYearOutput(this.getChildrenList()));
    }

    public JSONArray getYearOutput(ArrayList<Child> childrenList) {
        JSONArray children = new JSONArray();
        for (int i = 0; i < childrenList.size(); i++) {
            children.add(Main.getSimulation().getJsonChild(childrenList.get(i)));
        }
        return children;
    }

    public void writeFinalOutput(ArrayList<JSONArray> childrenJSONArray, int testNumber) {
        //cream jsonOuputul final
        JSONObject jsonObject = new JSONObject();
        JSONArray annualChildren = new JSONArray();
        for (int i = 0; i < childrenJSONArray.size(); i++) {
            JSONObject jsonAux = new JSONObject();
            jsonAux.put("children", childrenJSONArray.get(i));
            annualChildren.add(jsonAux);
        }
        jsonObject.put("annualChildren", annualChildren);

        //aici afisam outputul in fisierul sau
        ObjectMapper mapper = new ObjectMapper();
        String prettyJson = null;
        try {
            prettyJson = mapper.writerWithDefaultPrettyPrinter().writeValueAsString(jsonObject);
        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }

        try(FileWriter writer =
                    new FileWriter(Constants.OUTPUT_PATH + testNumber
                + Constants.FILE_EXTENSION)) {
            writer.write(prettyJson);
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //transformam preferintele copilului in stringuri potrivite
    //pentru output
    public static ArrayList<String> transformPreferencesForOutput(Child child) {
        ArrayList<String> preferenesList = new ArrayList<>();
        String auxString = new String();
        for (int i = 0; i < child.getGiftsPreferences().size(); i++) {
            auxString = child.getGiftsPreferences().get(i).toString();
            if (auxString.toUpperCase().compareTo("BOARD_GAMES") != 0) {
                auxString = capitalize(auxString.toLowerCase());
            } else {
                auxString = "Board Games";
            }
            preferenesList.add(auxString);
        }
        return preferenesList;
    }

    //functia intoarce Stringul nostru, dar cu
    //prima litera majuscula
    public static String capitalize(String str) {
        if(str == null || str.isEmpty()) {
            return str;
        }
        return str.substring(0, 1).toUpperCase() + str.substring(1);
    }

    //calculeaza suma scorurilor average (de la toti copiii)
    public Double calculateAverageScoreSum() {
        this.averageScoreSum = Double.valueOf(0);
        for (int i = 0; i < childrenList.size(); i++) {
            this.averageScoreSum = this.averageScoreSum + childrenList.get(i).calculateAverageScore();
        }
        return this.averageScoreSum;
    }
}
