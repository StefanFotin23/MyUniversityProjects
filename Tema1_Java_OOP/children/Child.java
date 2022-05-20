package children;

import Santa.Santa;
import enums.Category;
import enums.Cities;
import gifts.Gift;
import main.Main;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.util.ArrayList;

enum ageCategory {
    BABY,
    KID,
    TEEN,
    YOUNG_ADULT
}

public class Child {
    private final int id;
    private final String lastName;
    private final String firstName;
    private int age;
    private final Cities city;
    private ArrayList<Double> niceScore = new ArrayList<Double>();
    private ArrayList<Category> giftsPreferences = new ArrayList<Category>();
    private ageCategory category;
    private Double averageScore;
    private ArrayList<Gift> receivedGifts = new ArrayList<Gift>();
    private Double assignedBudget;
    private Double firstAssignedBudget;

    public Double getFirstAssignedBudget() {
        return firstAssignedBudget;
    }

    public void setFirstAssignedBudget(Double firstAssignedBudget) {
        this.firstAssignedBudget = firstAssignedBudget;
    }

    public Double getAssignedBudget() {
        return assignedBudget;
    }

    public void setAssignedBudget(Double assignedBudget) {
        this.assignedBudget = assignedBudget;
    }

    public ArrayList<Gift> getReceivedGifts() {
        return receivedGifts;
    }

    public void setReceivedGifts(ArrayList<Gift> receivedGifts) {
        this.receivedGifts = receivedGifts;
    }

    public int getId() {
        return id;
    }

    public String getLastName() {
        return lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public int getAge() {
        return age;
    }

    public Cities getCity() {
        return city;
    }

    public ArrayList<Double> getNiceScore() {
        return niceScore;
    }

    public ArrayList<Category> getGiftsPreferences() {
        return giftsPreferences;
    }

    public Double getAverageScore() {
        return averageScore;
    }

    public ageCategory getAgeCategory() {
        return category;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setAverageScore(Double averageScore) {
        this.averageScore = averageScore;
    }

    //copyConstructor
    public Child (Child original) {
        this.id = original.id;
        this.lastName = original.lastName;
        this.firstName = original.firstName;
        this.age = original.age;
        this.city = original.city;
        this.niceScore = original.niceScore;
        this.giftsPreferences = original.giftsPreferences;
        this.category = original.category;
        this.averageScore = original.averageScore;
        this.receivedGifts = original.receivedGifts;
    }

    public Child(JSONObject child, JSONArray giftsPreferences) {
        //mapam toate datele din JSON in obiectul-copil nou creat
        this.id = (int) (long) child.get("id");
        this.lastName = (String) child.get("lastName");
        this.firstName = (String) child.get("firstName");
        this.age = (int) (long) child.get("age");
        if ("Cluj-Napoca".compareTo((String) child.get("city")) != 0) {
            this.city = Cities.valueOf(((String) child.get("city")).toUpperCase());
        } else {
            this.city = Cities.valueOf("CLUJ");
        }
        this.niceScore.add((double) (int) (long) child.get("niceScore"));

        //pentru fiecare giftPreference din JSONArray,
        // adaugam in giftPreference-ul copilului,
        // toate categoriile de cadouri pe care le prefera,
        // dar datele sa fie convertite de la JSONObject
        // la Category type
        for (int i = 0 ; i < giftsPreferences.size(); i++) {
            Category auxCategory;
            if (giftsPreferences.get(i).toString().toUpperCase().compareTo("BOARD GAMES") != 0) {
                auxCategory = Category.valueOf((giftsPreferences.get(i).toString()).toUpperCase());
            } else {
                auxCategory = Category.valueOf("BOARD_GAMES");
            }
            this.giftsPreferences.add(auxCategory);
        }

        Main.getSimulation().getNiceScoreList().add(niceScore);

        if (niceScore == null) {
            //in case of bad input
            System.out.println("Child " + this.firstName + this.lastName +  " has negative niceScore!!!");
        }

        if (this.age < 0) {
            //in case of bad input
            System.out.println("Child " + this.firstName + this.lastName +  " has negative age!!!");
        } else if (this.age >= 0 && this.age < 5) {
            this.category = ageCategory.BABY;
            this.averageScore = this.calculateAverageScore();
        } else if (this.age >= 5 && this.age < 12) {
            this.category = ageCategory.KID;
            this.averageScore = this.calculateAverageScore();
        } else if (this.age >= 12 && this.age <= 18) {
            this.category = ageCategory.TEEN;
            this.averageScore = this.calculateAverageScore();
        } else if (this.age > 18){
            this.category = ageCategory.YOUNG_ADULT;
            this.averageScore = Double.valueOf(-1);
            //am pus -1 ca sa nu fie null (sa nu crape),
            // plus ca ne poate ajuta la debugging
            // in caz de nevoie
        }
    }

    //calculeaza averageScore, il modifica in memorie si
    //returneaza valoarea calculata
    public Double calculateAverageScore() {
        Double score = Double.valueOf(0);
        Double auxSum = Double.valueOf(0);

        if (this.category == ageCategory.YOUNG_ADULT) {
            //nu facem nimic
            //copilul este YOUNG_ADULT
            return score;
        }
        if (this.category == ageCategory.BABY) {
            score = Double.valueOf(10);
        } else if (this.category == ageCategory.KID){
            for (int i = 0; i < this.niceScore.size(); i++) {
                auxSum = auxSum + this.niceScore.get(i);
            }
            score = auxSum / this.niceScore.size();
        } else if (this.category == ageCategory.TEEN) {
            //facem formula pt media ponderata
            for (int i = 0; i < this.niceScore.size(); i++) {
                auxSum = auxSum + (i + 1) * this.niceScore.get(i);
            }
            score = (2 * auxSum) / (this.niceScore.size() * (this.niceScore.size() + 1));
        }
        this.averageScore = score;
        return score;
    }

    public Double calculateAssignedBudget(Santa santa) {
        this.assignedBudget = santa.budgetUnit * this.calculateAverageScore();
        this.firstAssignedBudget = this.assignedBudget;
        return this.assignedBudget;
    }
}
