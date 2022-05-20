package Santa;

import children.Child;
import enums.Category;
import gifts.Gift;
import main.*;

import java.util.ArrayList;

public class Santa {
    public Double santaBudget = Double.valueOf(0);
    public Double budgetUnit = Double.valueOf(0);
    public ArrayList<Gift> santaGiftsList = new ArrayList<Gift>();

    public Santa() {
        //nu facem nimic
    }

    public ArrayList<Gift> getSantaGiftsList() {
        return santaGiftsList;
    }

    public void setSantaGiftsList(ArrayList<Gift> santaGiftsList) {
        this.santaGiftsList = santaGiftsList;
    }

    public Double getSantaBudget() {
        return this.santaBudget;
    }

    public void setSantaBudget(Double santaBudget) {
        this.santaBudget = santaBudget;
    }

    public Double calculateBudgetUnit() {
        this.budgetUnit = this.santaBudget / Main.getSimulation().getAverageScoreSum();
        return this.budgetUnit;
    }

    public void giveGiftsToChild(Child child) {
        //aici memoram cadoul cu pretul minim (pe care il va darui mosul)
        Gift gift = null;
        //verificam pentru fiecare categorie din preferintele lui
        for (int j = 0; j < child.getGiftsPreferences().size(); j++) {
            //resetam gift-ul, pentru ca inca nu am assignat vreunul
            //in caz ca nu gasim niciunul
            gift = null;
            //aici verificam daca categoria pe care o prefera copilul,
            // se regaseste si intre cadourile mosului
            for (int l = 0; l < this.santaGiftsList.size(); l++) {
                //daca categoria pe care o vrea copilul,
                // se regaseste in lista de cadouri ale mosului,
                // atunci il alegem pe cel mai ieftin si il
                //daruim copilului
                if (child.getGiftsPreferences().get(j).compareTo
                        (santaGiftsList.get(l).getCategory()) == 0) {
                    if (gift == null) {
                        gift = new Gift(santaGiftsList.get(l));
                    } else {
                        if (santaGiftsList.get(l).getPrice() < gift.getPrice()) {
                            gift = new Gift(santaGiftsList.get(l));
                        }
                    }
                }
            }
            if (gift != null) {
                if (child.getAssignedBudget() >= gift.getPrice()) {
                    child.getReceivedGifts().add(gift);
                    child.setAssignedBudget(child.getAssignedBudget() - gift.getPrice());
                }
            }
        }
    }
}
