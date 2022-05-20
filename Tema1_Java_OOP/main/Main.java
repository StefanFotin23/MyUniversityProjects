package main;

import checker.Checker;
import children.Child;
import children.ChildUpdate;
import common.Constants;
import gifts.Gift;
import org.json.simple.JSONArray;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * Class used to run the code
 */
public final class Main {
    static Simulation current_simulation;

    private Main() {
        ///constructor for checkstyle
    }

    public static Simulation getSimulation() {
        return current_simulation;
    }

    public static void setSimulation(Simulation simulation) {
        current_simulation = simulation;
    }

    /**
     * This method is used to call the checker which calculates the score
     *
     * @param args the arguments used to call the main method
     */
    public static void main(final String[] args) throws IOException {
        Child auxNewChild;
        ChildUpdate auxChildUpdate;
        Gift auxNewGift;
        //aici avem variabilele care sunt auxiliare, ajutatoare

        //cream directorul de output, unde o sa cream cele 25 de fisiere (goale)
        //apoi le vom scrie, dupa ce procesam datele
        Path output = Paths.get("output");
        if (Files.exists(output) == Boolean.parseBoolean(null)) {
            Files.createDirectories(output);
        }
        for (int i = 1; i <= Constants.TESTS_NUMBER; i++) {
            File file = new File(Constants.OUTPUT_PATH + i
                    + Constants.FILE_EXTENSION);
            file.createNewFile();
        }

        //tratam fiecare test, pe rand
        for (int i = 1; i <= 25/*Constants.TESTS_NUMBER*/; i++) {
            Simulation simulation = new Simulation();
            Main.setSimulation(simulation);
            //ne-am creat si setat o simulare noua (independenta)
            simulation.readTestInput(i);
            //simulam primul an
            simulation.SimulatingYear(simulation.getSanta());
            //acum urmeaza ceilalti ani
            for (int j = 1; j < simulation.numberOfYears; j++) {
                //cream o lista noua JSONArray "children",
                //pe care o vom popula ulterior cu copiii,
                //din anul curent, cu datele modificate
                JSONArray jsonNewYearlyChildren = new JSONArray();
                simulation.setJsonYearlyChildren(jsonNewYearlyChildren);
                //inainte sa simulam urmatorul an,
                // updatam datele de intrare
                for (int l = 0; l < simulation.getChildrenList().size(); l++) {
                    //pentru copilul l
                    int age = simulation.getChildrenList().get(l).getAge();
                    age++;
                    simulation.getChildrenList().get(l).setAge(age);
                    if (age > 18) {
                        simulation.getChildrenList().remove(l);
                    }
                }
                for (int l = 0; l < simulation.getChildrenList().size(); l++) {
                    //trebuie sa updatam fiecare copil
                    for (int h = 0; h < simulation.getAnnualChanges().get(j).getChildrenUpdates().size(); h++) {
                        auxChildUpdate = simulation.getAnnualChanges().get(j).getChildrenUpdates().get(h);
                        if (auxChildUpdate.getId() == simulation.getChildrenList().get(l).getId()) {
                            if (auxChildUpdate.getNiceScore() != -1) {
                                simulation.getChildrenList().get(l).getNiceScore().add(auxChildUpdate.getNiceScore());
                            }
                            for (int k = auxChildUpdate.getGiftsPreferences().size() - 1; k >= 0; k--) {
                                simulation.getChildrenList().get(l).getGiftsPreferences().
                                        add(0, auxChildUpdate.getGiftsPreferences().get(k));
                            }
                        }
                    }
                }
                //pentru fiecare copil nou
                for (int l = 0; l < simulation.getAnnualChanges().get(j).getNewChildren().size(); l++) {
                    auxNewChild = simulation.getAnnualChanges().get(j).getNewChildren().get(l);
                    if (auxNewChild.getAge() <= 18) {
                        simulation.getChildrenList().add(auxNewChild);
                    }
                }
                //actualizam bugetul mosului
                simulation.getSanta().setSantaBudget(simulation.getAnnualChanges().get(j).getNewSantaBudget());
                //actualizam cadourile mosului
                for (int l = 0; l < simulation.getAnnualChanges().get(j).getNewGifts().size(); l++) {
                    auxNewGift = simulation.getAnnualChanges().get(j).getNewGifts().get(l);
                    simulation.getSanta().getSantaGiftsList().add(auxNewGift);
                }
                simulation.SimulatingYear(simulation.getSanta());
            }
            //System.out.println(simulation.getJsonYearlyChildren());
            simulation.writeFinalOutput(simulation.getJsonYearlyChildren(), i);
        }
        //aici se sfarseste implementarea, urmeaza checkerul
        //Checker.calculateScore();
    }
}
