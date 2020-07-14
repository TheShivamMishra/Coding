import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

public class Questions {

    public static void main(String[] args) {
        List<String> wordDict = new ArrayList<String>();
        wordDict.add("apple");
        wordDict.add("pen");
        wordDict.add("applepen");
        wordDict.add("pine");
        wordDict.add("pineapple");
        System.out.println(wordBreak("pineapplepenapple", wordDict));

    }

   
    public static  HashSet<String> map = new HashSet<>();

    public static boolean wordBreak(String s, List<String> wordDict) {
        for (String str : wordDict) {
            map.add(str);
        }
        // System.out.println(map);
        // HashMap<String, Boolean> dp = new HashMap<>();

        // boolean res = wordBreak_(s, dp);
        // System.out.println(dp);
        wordBreakII(s, "");
        System.out.println(myAns);
        return true;
    }

    // LeetCode Word Break 139
    // =======================================================================
    public static boolean wordBreak_(String s, HashMap<String, Boolean> dp) {
        if (s.length() == 0)
            return true;
        if (dp.containsKey(s))
            return dp.get(s);

        boolean res = false;
        for (int i = 1; i <= s.length(); i++) {
            String newStr = s.substring(0, i);
            if (map.contains(newStr)) {
                res = res || wordBreak_(s.substring(i), dp);
            }
        }

        dp.put(s, res);
        return res;
    }
    
    // leetcode word break 140 ===============================================
    static List<String> myAns = new ArrayList<>();
    public static void wordBreakII(String s, String ans) {
        if (s.length() == 0) {
            myAns.add(ans.substring(0,ans.length()-1));
            return;
        }

        for (int i = 1; i <= s.length(); i++) {
            String newStr = s.substring(0, i);
            if (map.contains(newStr)) {
                wordBreakII(s.substring(i), ans+newStr + " ");
            }
        }

    }

}