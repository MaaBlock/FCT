import { defineConfig } from 'vitepress'
import { MermaidMarkdown,MermaidPlugin } from "vitepress-plugin-mermaid";

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "FCT 文档",
  description: "",
    base: '/FCT/',
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
        { text: '主页', link: '/' },
        { text: '文档', link: '/document/index.md'},
        { text: 'api', link: '/api/zh/html/index.html',target: '_blank' },
    ],


      sidebar: [
          {
              text: '文档',
              link: '/document/index.md',
              items: [
                  {
                      text: '关于',
                      link: '/document/about/index.md',
                      items: []
                  },
                  {
                      text: '入门',
                      link: '/document/getting_started/index.md',
                      items: [
                          {
                              text: '快速开始',
                              link: '/document/getting_started/quick-start/index.md',
                              items: [
                                  {text: '配置vcpkg',link: '/document/getting_started/quick-start/config-vcpkg.md' },
                                  {text: '配置ide',
                                      items: [
                                          {text: 'VS 2022' },
                                          {text: 'CLion', link: '/document/getting_started/quick-start/install-for-clion.md' },
                                      ]
                                  }
                              ]
                          }]
                  },
                  {
                      text: '手册',
                      link: '/document/tutorials/index.md',
                      items: [
                          {

                          }]
                  },
                  {
                      text: '贡献',
                      link: '/document/contributing/index.md',
                      items: [
                          {
                              text: '参与开发',
                              link: '/document/contributing/development/index.md',
                              items: [
                                  {
                                      text: '上层架构',
                                      link: '/document/contributing/development/highlevel/index.md',
                                      items: [
                                          { text: 'RenderGraph的编译流程',link: '/document/contributing/development/highlevel/rendergraph-compile.md' },
                                      ]
                                  }
                              ]
                          }
                      ]
                  }
              ]
          }
      ],


      socialLinks: [
          { icon: 'github', link: 'https://github.com/MaaBlock/FCT' }
      ]
  },

    ignoreDeadLinks: true,
    markdown: {
        config(md) {
            md.use(MermaidMarkdown);
        }
    },
    vite : {
        plugins: [MermaidPlugin()],
        optimizeDeps: {
            include: 'mermaid',
        },
        ssr: {
            noExternal: ['mermaid'],
        },
    },
})
