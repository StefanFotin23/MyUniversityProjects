package children;

import enums.Category;
import gifts.Gift;
import main.Main;
import main.Simulation;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.util.ArrayList;

public class ChildUpdate {
    private int id;
    private double niceScore;
    private ArrayList<Category> giftsPreferences = new ArrayList<Category>();

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getNiceScore() {
        return niceScore;
    }

    public void setNiceScore(double niceScore) {
        this.niceScore = niceScore;
    }

    public ArrayList<Category> getGiftsPreferences() {
        return giftsPreferences;
    }

    public void setGiftsPreferences(ArrayList<Category> giftsPreferences) {
        this.giftsPreferences = giftsPreferences;
    }

    //copyConstructor
    public ChildUpdate(ChildUpdate original) {
        this.id = original.id;
        this.niceScore = original.niceScore;
        this.giftsPreferences = original.giftsPreferences;
    }

    public ChildUpdate(JSONObject childUpdate) {
        if (childUpdate != null) {
            int auxID;
            //luam Id-ul copilului pe care vrem sa-l updatam
            auxID = (int) (long) childUpdate.get("id");
            //cautam in lista de copii dupa Id-ul respectiv
            for (int i = 0; i < Main.getSimulation().getChildrenList().size(); i++) {
                //daca gasim Id-ul respectiv, salvam datele pentru acest childUpdate
                //in caz contrat, le ignoram
                //deoarece ni s-a dat sa updatam un copil care nu exista deja
                //(also...am observat ca avem inputuri "capcana",
                // deci reprezinta o metoda de protectie)
                if (Main.getSimulation().getChildrenList().get(i).getId() == auxID) {
                    //daca niceScoreul e null, nu putem updata/crea un copil,
                    // deci ignoram acest input
                    if (childUpdate.get("niceScore") != null) {
                        this.niceScore = (double) (int) (long) childUpdate.get("niceScore");
                    } else {
                        this.niceScore = -1;
                    }
                    JSONArray jsonGiftPreferences = (JSONArray) childUpdate.get("giftsPreferences");
                    Category auxCategory;
                    for (int j = 0; j < jsonGiftPreferences.size(); j++) {
                        if (jsonGiftPreferences.get(j).toString().toUpperCase().compareTo("BOARD GAMES") != 0) {
                            auxCategory = Category.valueOf((jsonGiftPreferences.get(j).toString()).toUpperCase());
                        } else {
                            auxCategory = Category.valueOf("BOARD_GAMES");
                        }
                        this.giftsPreferences.add(auxCategory);
                    }
                    this.id = auxID;
                }
            }
        }
    }
}
