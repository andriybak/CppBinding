import java.io.File;

public class BindingJava
{
    static
    {
        File lib = new File("../CppBinding.dll");
        System.load(lib.getAbsolutePath());
    }

    private native long CreateStyleOptionsInstance();
    private native long CreateStyleWithStyleURL(long StyleOptionsInstance, String url);
    private native void DestroyStyleOptionsInstance(long StyleOptionsInstance);
    
    private native long CreateMapInstance();
    private native long SetMapStyle(long MapInstance, long StyleOptionsInstance);
    private native void RenderMap(long MapInstance, String CallbackName);
    private native void DestroyMapInstance(long MapInstance);

    public class StyleOptions
    {
        private long InstancePointer;

        StyleOptions()
        {
            this.InstancePointer = CreateStyleOptionsInstance();
        }

        public void SetStyleWithUrl(String url)
        {
            this.InstancePointer = CreateStyleWithStyleURL(this.InstancePointer, url);
        }

        public long GetInstancePointer()
        {
            return this.InstancePointer;
        }
    }

    public class StyledMap
    {
        private long InstancePointer;

        StyledMap()
        {
            this.InstancePointer = CreateMapInstance();
        }

        public void SetStyle(StyleOptions Style)
        {
            this.InstancePointer = SetMapStyle(this.InstancePointer, Style.GetInstancePointer());
        }

        public void Render(String CallbackName)
        {
            try
            {
                RenderMap(this.InstancePointer, CallbackName);
            }
            catch(Error e)
            {
                System.out.println(e.getMessage());
            }
        }

        public long GetInstancePointer()
        {
            return this.InstancePointer;
        }
    }

    private void render()
    {
        System.out.println("map rendered in Java!");
    }
  
    public static void main(String[] args)
    {
        BindingJava JavaBindingTest = new BindingJava();
        StyleOptions Options = JavaBindingTest.new StyleOptions();
        Options.SetStyleWithUrl("www.test.com");

        StyledMap Map = JavaBindingTest.new StyledMap();
        Map.SetStyle(Options);
        Map.Render("render");

        JavaBindingTest.DestroyStyleOptionsInstance(Options.GetInstancePointer());
        JavaBindingTest.DestroyMapInstance(Map.GetInstancePointer());
    }
}