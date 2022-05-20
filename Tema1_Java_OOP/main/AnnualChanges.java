package main;

import children.ChildUpdate;
import gifts.Gift;
import children.Child;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.util.ArrayList;

public class AnnualChanges {
    private Double newSantaBudget;
    private ArrayList<Gift> newGifts = new ArrayList<Gift>();
    private ArrayList<Child> newChildren = new ArrayList<Child>();
    private ArrayList<ChildUpdate> childrenUpdates = new ArrayList<ChildUpdate>();

    //copyConstructor
    public AnnualChanges (AnnualChanges original) {
        this.newSantaBudget = original.newSantaBudget;
        this.newGifts = original.newGifts;
        this.newChildren = original.newChildren;
        this.childrenUpdates = original.childrenUpdates;
    }

    public AnnualChanges (JSONObject annualChanges, JSONArray jsonNewGifts, JSONArray jsonNewChildren,
                          JSONArray jsonChildrenUpdates) {
        this.newSantaBudget = (double) (int) (long) annualChanges.get("newSantaBudget");
        if (jsonNewGifts != null) {
            Gift auxGift;
            for (int i = 0; i < jsonNewGifts.size(); i++) {
                auxGift = new Gift((JSONObject) jsonNewGifts.get(i));
                this.newGifts.add(auxGift);
            }
        }
        if (jsonNewChildren != null) {
            Child auxChild;
            for (int i = 0; i < jsonNewChildren.size(); i++) {
                JSONArray jsonNewGiftPreferences =
                        (JSONArray) ((JSONObject) jsonNewChildren.get(i)).get("giftsPreferences");
                auxChild = new Child((JSONObject) jsonNewChildren.get(i), jsonNewGiftPreferences);
                this.newChildren.add(auxChild);
            }
        }
        if (jsonChildrenUpdates != null) {
            ChildUpdate auxChildUpdate;
            for (int i = 0 ; i < jsonChildrenUpdates.size(); i++) {
                auxChildUpdate = new ChildUpdate((JSONObject) jsonChildrenUpdates.get(i));
                this.childrenUpdates.add(auxChildUpdate);
            }
        }
    }

    public Double getNewSantaBudget() {
        return newSantaBudget;
    }

    public void setNewSantaBudget(Double newSantaBudget) {
        this.newSantaBudget = newSantaBudget;
    }

    public ArrayList<Gift> getNewGifts() {
        return newGifts;
    }

    public void setNewGifts(ArrayList<Gift> newGifts) {
        this.newGifts = newGifts;
    }

    public ArrayList<Child> getNewChildren() {
        return newChildren;
    }

    public void setNewChildren(ArrayList<Child> newChildren) {
        this.newChildren = newChildren;
    }

    public ArrayList<ChildUpdate> getChildrenUpdates() {
        return childrenUpdates;
    }

    public void setChildrenUpdates(ArrayList<ChildUpdate> childrenUpdates) {
        this.childrenUpdates = childrenUpdates;
    }
}
