using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

namespace TestWebCore.Controllers
{
    public class TestController : Controller
    {
        public IActionResult Index()
        {
            string.IsNullOrEmpty("core mua");
            return View();
        }
    }
}
