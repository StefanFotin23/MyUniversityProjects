package gifts;

import enums.Category;
import org.json.simple.JSONObject;

public class Gift {
    private String productName;
    private Double price;
    private Category category;

    //copyConstructor
    public Gift(Gift original) {
        this.productName = original.productName;
        this.price = original.price;
        this.category = original.category;
    }

    public Gift(JSONObject gift) {
        this.productName = (String) gift.get("productName");
        this.price = (double) (int) (long) gift.get("price");
        if (((String) gift.get("category")).compareTo("Board Games") != 0) {
            this.category = Category.valueOf(((String) gift.get("category")).toUpperCase());
        } else {
            this.category = Category.valueOf("BOARD_GAMES");
        }
    }

    public JSONObject getJSONGift() {
        JSONObject jsonGift = new JSONObject();
        jsonGift.put("productName", this.getProductName());
        jsonGift.put("price", this.getPrice());
        jsonGift.put("category", this.getCategory());
        return jsonGift;
    }

    public String getProductName() {
        return productName;
    }

    public void setProductName(String productName) {
        this.productName = productName;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public Category getCategory() {
        return category;
    }

    public void setCategory(Category category) {
        this.category = category;
    }
}
